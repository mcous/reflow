// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: reflow.cpp
// description: application file for the reflow oven controller

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/sleep.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "reflow.h"
#include "display.h"

// macro for event checking
#define event(T, M) ((T & M) == M)

// ISR for ADC readings
// ISR(ADC_vect) {
//   // disable sleep
//   SMCR = 0;
//   // read the ADC reading into the buffer
//   adcRead = (ADCH << 8) | (ADCL);
// }

// ISR for rotary encoder
ISR(ENCODER_PCINT_vect) {
  e.handleChange();
}

// applicaiton event timer
ISR(REFLOW_EVENT_vect) {
  // set the flags
  // display refresh
  if (event(eventTimer, REFLOW_DISPLAY_EVENT)) {
    eventFlags |= REFLOW_DISPLAY_FLAG;
  }
  // button polling
  if (event(eventTimer, REFLOW_BUTTON_EVENT)) {
    eventFlags |= REFLOW_BUTTON_FLAG; 
  }
  // encoder reading
  if (event(eventTimer, REFLOW_ENCODER_EVENT)) {
    eventFlags |= REFLOW_ENCODER_FLAG;
  }
  // temperature reading
  if (event(eventTimer, REFLOW_THERMO_EVENT)) {
    eventFlags |= REFLOW_THERMO_FLAG;
  }

  // increment the counter and overflow if necessary
  eventTimer = (eventTimer < REFLOW_EVENT_MAX) ? eventTimer+1 : 0; 
}

// application main method
int main(void) {
  // disable global interrupts for setting stuff
  cli();

  // ISR volatiles
  // should already be 0 but hey safety first
  adcRead = 0;
  //tempCheck = false;
  eventTimer = 0;
  eventFlags = 0;

  // get the display ready
  Display disp;
  disp.init();
  // get the buttons and encoder input ready
  Buttons b;
  b.init();
  e.init();
  uint8_t encoderCount = MODE_SET_DISPLAY_COUNT;
  // initialize the indicator LEDs
  initLeds();

  // temperature
  initThermo();
  bool targetHit = false;
  Celsius temp;
  Celsius target;
  target.set(200);
  uint8_t tempUnits = TEMP_UNIT_C;

  // text buffer for temperature display
  char d[7];
  uint8_t dLen = temp.toString(d);
  char s[7];
  uint8_t sLen = target.toString(s);

  // operating mode
  uint8_t mode = MODE_OFF;
  LED_PORT = (LED_PORT & ~LED_MASK) | LED_STOP;
  //uint8_t prevMode = mode;

  // enable the event timer
  enableEventTimer();

  // enable global interrupts
  sei();

  // sideways eight loop
  for (;;) {
    // take care of any events
    // display refresh
    if (eventFlags & REFLOW_DISPLAY_FLAG) {
      // refresh that shit yo
      disp.refresh();
      // clear the flag
      eventFlags &= ~REFLOW_DISPLAY_FLAG;
    }
    // button polling
    if (eventFlags & REFLOW_BUTTON_FLAG) {
      // poll that shit yo
      b.handleTimer();
      // clear the flag
      eventFlags &= ~REFLOW_BUTTON_FLAG;
    }
    // encoder reading
    if (eventFlags & REFLOW_ENCODER_FLAG) {
      // read that shit yo
      int8_t enc = e.getChange();
      if (enc) {
        encoderCount=0;
        target.setScaled(target.getScaled() + 2*enc, TEMP_POWER);
        // underflow protection
        if (target < 0) {
          target.set(0);
        }
        sLen = target.toString(tempUnits, s);
      }
      // increment counter
      if (encoderCount < MODE_SET_DISPLAY_COUNT) {
        encoderCount++;
      }
      // clear the flag
      eventFlags &= ~REFLOW_ENCODER_FLAG;
    }
    // thermometer reading
    if (eventFlags & REFLOW_THERMO_FLAG) {
      // measure that shit yo
      // take 4 ADC samples and divide by 2 to oversample to 11-bit precision
      // then, convert 11-bit number to 4x degrees C
      // steps combined for efficiency
      uint32_t c = 0;
      for (uint8_t i=4; i>0; i--) {
        // start an ADC conversion
        ADCSRA |= (1<<ADSC);
        // wait for conversion to complete
        while (ADCSRA & (1<<ADSC));
        c += ( ADCL | (ADCH << 8) );
      }
      c *= 25 * VREF;
      c >>= 7;
      temp.setScaled((int16_t)(c), TEMP_POWER);
      dLen = temp.toString(tempUnits, d);
      // clear the flag
      eventFlags &= ~REFLOW_THERMO_FLAG;
    }


    // check for open thermocouple
    if (temp > 500) {
      // write error flag
      mode |= MODE_ERR;
    }
    // else thermo data is good
    else {
      // clear error flag
      mode &= ~MODE_ERR;
      // check if we're displaying the set temp
      if (encoderCount < MODE_SET_DISPLAY_COUNT) {
        mode |= MODE_SET;
      }
      else {
        mode &= ~ MODE_SET;
        if (mode & MODE_ON && (!targetHit)) {
          if (temp < target) {
            HEAT_PORT |= HEAT_PIN;
          }
          else {
            targetHit = true;
            HEAT_PORT &= ~HEAT_PIN;
          }
        }
      }
    }

    // set the display
    // error is first priority, then set, then value
    if (mode & MODE_ERR) {
      char e[5] = {'e', 'r', 'r', '0', '\0'};
      disp.set(e, 4);
    }
    else if (mode & MODE_SET) {
      disp.set(s, sLen);
    }
    else {
      disp.set(d, dLen);
    }

    // handle buttons
    uint8_t buttons;
    //  button presses
    if (b.getPress(&buttons)) {
      if (buttons == BUTTON_SET) {
        // toggle units
        tempUnits ^= TEMP_UNIT_F;
      } 
      else if (buttons == BUTTON_START) {
        mode |= MODE_ON;
        LED_PORT = (LED_PORT & ~LED_MASK) | LED_START;
        targetHit = false;
      }
      else {
        mode &= ~MODE_ON;
        LED_PORT = (LED_PORT & ~LED_MASK) | LED_STOP;
        HEAT_PORT &= ~HEAT_PIN;
      }
    }

    // handle encoder input
    // int8_t enc = e.getChange();
    // if (enc && mode == MODE_SET) {
    //   setTemp.setScaled(setTemp.getScaled() + 2*enc, TEMP_POWER);
    //   // underflow protection
    //   if (setTemp < 0) {
    //     setTemp.set(0);
    //   }
    //   sLen = setTemp.toString(s);
    // }

    // refresh the display
    // disp.refresh();
  }

  // DEEP THOUGHT
  return 42;
}

// event timer
void enableEventTimer(void) {
  // enable timer 1 to fire at 512Hz
  // CTC mode, no prescaler, OCR1A = 15625
  TCCR1A = 0;
  TCCR1B = ( (1<<WGM12) | (1<<CS10) );
  TCCR1C = 0;
  OCR1A = 15625;
  // enable the compare interrupt
  TIMSK1 = (1<<OCIE1A);
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
  // slow things down to 8 MHz / 64 = 125 kHz
  ADCSRA |= ( (1<<ADPS2) | (1<<ADPS1) );
  // enable ADC, do a reading, and toss it
  ADCSRA |= ( (1<<ADEN) | (1<<ADSC) );
  // wait for conversion to complete
  while (ADCSRA & (1<<ADSC));
  // clear the bit (extended conversion)
  //ADCSRA &= ~(1<<ADSC);
  // read the value;
  uint16_t read = ADCL | (ADCH << 8);
  (void) read;
}

// convert the ADC value from the thermocouple to 4x the temperature in C
// 4x C is chosen because it allows us to put the temp with 0.25 deg precision in a 16-bit int
// Celsius readThermo(void) {
//   Celsius ret;
//   uint16_t c;
//   ATOMIC_BLOCK(ATOMIC_FORCEON) {
//     c = adcRead;
//   }
//   // hey look, math
//   //   C = (ADCread * VREF V)/1024 * (1 deg C)/(5 mV)
//   //   C = (ADCread * VREF V)/1024 * (200 deg C)/(1 V)
//   //   C = (ADCread * VREF * 25 deg C)/128
//   //  4C = (ADCread * VREF * 25 deg C)/32
//   c = c * VREF * 25;
//   c >>= 5;
//   ret.setScaled(c, TEMP_POWER);
//   return ret;
// }

