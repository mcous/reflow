// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: reflow.cpp
// description: application file for the reflow oven controller

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "reflow.h"
#include "display.h"

// ISR for ADC readings
ISR(ADC_vect) {
  // read the ADC reading into the buffer
  adcRead = ADCL | (ADCH << 8);
}

// ISR for temperature readings
ISR(TIMER1_OVF_vect) {
  tempCheck = true;
}

// ISR for rotary encoder
ISR(ENCODER_PCINT_vect) {
  e.handleChange();
}

// ISR for switch inputs
ISR(BUTTON_PCINT_vect, ISR_NOBLOCK) {
  b.handleChange();
}

// switch debouncer / timer
ISR(TIMER2_OVF_vect, ISR_NOBLOCK) {
  b.handleTimer();
}

// application main method
int main(void) {
  // disable global interrupts for setting stuff
  cli();

  // ISR volatiles
  // should already be 0 but hey safety first
  adcRead = 0;
  tempCheck = false;

  // get the display ready
  Display disp;
  disp.init();
  // get the buttons and encoder input ready
  b.init();
  e.init();
  // initialize the indicator LEDs
  initLeds();

  // temperature
  initThermo();
  bool targetHit = false;
  Celsius temp;
  Celsius setTemp;
  Celsius target;
  setTemp.set(200);

  // perform temperature readings about every 30 ms
  // ensure timer0 settings are cleared out
  TCCR1A = 0;
  // set prescaler to 1024
  TCCR1B = ( (1 << CS11) | (1 << CS10) );
  // enable the overflow interrupt
  TIMSK1 = (1 << TOIE1);


  // operating mode
  uint8_t mode = MODE_OFF;
  LED_PORT = (LED_PORT & ~LED_MASK) | LED_STOP;
  uint8_t prevMode = mode;

  // enable global interrupts
  sei();

  // sideways eight loop
  for (;;) {
    // check the temperature if it's time
    if (tempCheck) {
      tempCheck = false;
      temp = readThermo();
    }
    // check for open thermocouple
    if (temp > 1600) {
      mode = MODE_ERR;
    }

    // handle the temperature if we're on
    if ((mode == MODE_ON) && (!targetHit)) {
      if (temp < target) {
        HEAT_PORT |= HEAT_PIN;
      }
      else {
        targetHit = true;
        HEAT_PORT &= ~HEAT_PIN;
      }
    }

    // set the display
    if (mode == MODE_ON || mode == MODE_OFF) {
      disp.set(temp.getScaled()/4.0);
    }
    else if (mode == MODE_SET) {
      disp.set(setTemp.getScaled()/4.0);
    }
    else if (mode == MODE_ERR) {
      disp.setErr(ERROR_THERMO_OPEN);
    }

    // handle buttons
    uint8_t buttons;
    //  button presses
    if (b.getPress(&buttons)) {
      if (buttons == BUTTON_SET) {
        if (mode == MODE_SET) {
          target = setTemp;
          mode = prevMode;
        }
        else {
          prevMode = mode;
          mode = MODE_SET;
        }
      } 
      else if (buttons == BUTTON_START) {
        mode = MODE_ON;
        LED_PORT = (LED_PORT & ~LED_MASK) | LED_START;
        targetHit = false;
      }
      else {
        mode = MODE_OFF;
        LED_PORT = (LED_PORT & ~LED_MASK) | LED_STOP;
        HEAT_PORT &= ~HEAT_PIN;
      }
    }
    // button holds
    if (b.getHold(&buttons)) {
      // do nothing
      break;
    }

    // handle encoder input
    int8_t enc = e.getChange();
    if (mode == MODE_SET) {
      setTemp.setScaled(setTemp.getScaled() + 2*enc, TEMP_POWER);
      // underflow protection
      if (setTemp < 0) {
        setTemp.set(0);
      }
    }

    // refresh the display
    disp.refresh();
  }

  // DEEP THOUGHT
  return 42;
}

void initLeds(void) {
  // set pins as outputs
  DDR(LED_PORT) |= LED_MASK;
  // set pins to low (off)
  LED_PORT &= ~LED_MASK;
}

void initHeat(void) {
  // set heater to output
  DDR(HEAT_PORT) |= HEAT_PIN;
  // set low (off)
  HEAT_PORT &= ~HEAT_PIN;
}

// intialize thermocouple reading
void initThermo(void) {
  // set up ADC on ADC7 with VREF as the reference voltage
  ADMUX = 7;
  // enable ADC, do a reading, and toss it
  ADCSRA |= ( (1<<ADEN) | (1<<ADSC) );
  // wait for conversion to complete
  while (ADCSRA & (1<<ADSC));
  // read the value;
  uint16_t read = ADCL | (ADCH << 8);
  (void) read;
  // put ADC into free-running mode, enable the interrupt, and slow things down
  ADCSRA |= ( (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2));
}

// convert the ADC value from the thermocouple to 4x the temperature in C
// 4x C is chosen because it allows us to put the temp with 0.25 deg precision in a 16-bit int
Celsius readThermo(void) {
  Celsius ret;
  int16_t c;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    c = adcRead;
  }
  // hey look, math
  //   C = (ADCread * VREF V)/1024 * (1 deg C)/(5 mV)
  //   C = (ADCread * VREF V)/1024 * (200 deg C)/(1 V)
  //   C = (ADCread * VREF * 25 deg C)/128
  //  4C = (ADCread * VREF * 25 deg C)/32
  c = c * VREF * 25;
  c >>= 5;
  ret.setScaled(c, TEMP_POWER);
  return ret;
}

