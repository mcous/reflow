// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: reflow.cpp
// description: application file for the reflow oven controller

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "reflow.h"
#include "display.h"

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
  // diable global interrupts for setting stuff
  cli();

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
  float temp = 0;
  float setTemp = 200;
  float target = 0;

  // operating mode
  uint8_t mode = MODE_OFF;
  LED_PORT = (LED_PORT & ~LED_MASK) | LED_STOP;
  uint8_t prevMode = mode;

  // enable global interrupts
  sei();

  // sideways eight loop
  for (;;) {
    // get the temperature
    temp = readThermo();
    // check for open thermocouple
    if (temp > 400) {
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
      disp.set(temp);
    }
    else if (mode == MODE_SET) {
      disp.set(setTemp);
    }
    else if (mode == MODE_ERR) {
      disp.setErr();
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
      setTemp += 0.5*enc;
      // underflow protection
      if (setTemp < 0) {
        setTemp = 0;
      }
    }

    // refresh the display
    disp.refresh();
    // slight delay
    _delay_ms(2);

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
  // enable ADC
  ADCSRA |= (1<<ADEN);
  // do a reading and toss it
  ADCSRA |= (1<<ADSC);
  // wait for conversion to complete
  while (ADCSRA & (1<<ADSC));
  // read the value;
  uint16_t read = ADCL | (ADCH << 8);
  (void) read;
}

// read the thermocouple
float readThermo(void) {
  // start a ADC conversion
  ADCSRA |= (1<<ADSC);
  // wait for conversion to complete
  while (ADCSRA & (1<<ADSC));
  // read the value;
  uint16_t read = ADCL | (ADCH << 8);
  // convert the value to temperature
  float volts = (read * vref)/1024.0;
  return (volts / 0.005);
}

