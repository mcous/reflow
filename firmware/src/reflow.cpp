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
#include "buttons.h"
#include "celsius.h"

// macro for event checking
#define event(T, M) ((T & M) == M)

// pin change ISR for rotary encoder
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
  uint8_t buttonCount  = MODE_SET_MODE_COUNT;
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
  uint8_t mode = MODE_OFF | MODE_HIT;
  LED_PORT = (LED_PORT & ~LED_MASK) | LED_STOP;

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
      // handle buttons
      uint8_t buttons;
      //  button presses
      if (b.getHold(&buttons)) {
        // if set switch is held, switch units
        if (buttons == BUTTON_SET) {
          tempUnits ^= TEMP_UNIT_F;
        } 
      }
      else if (b.getPress(&buttons)) {
        if (buttons == BUTTON_START) {
          mode |= MODE_ON;
          targetHit = false;
        }
        else if (buttons == BUTTON_STOP) {
          mode &= ~MODE_ON;
          HEAT_PORT &= ~HEAT_PIN;
        }
        else if (buttons == BUTTON_SET) {
          buttonCount = 0;
          mode ^= (MODE_HIT | MODE_HOLD);
        }
      }
      // increment counter
      if (buttonCount < MODE_SET_MODE_COUNT) {
        buttonCount++;
      }
      // clear the flag
      eventFlags &= ~REFLOW_BUTTON_FLAG;
    }
    // encoder reading
    if (eventFlags & REFLOW_ENCODER_FLAG) {
      // read that shit yo
      int8_t enc = e.getChange();
      if (enc) {
        encoderCount=0;
        // change target based on encoder speed
        // slower = less increments
        if (enc == -1) {
          target--;
          target--;
        }
        else if (enc == 1) {
          target++;
          target++;
        }
        else if (enc == -2) {
          target -= 1;
        }
        else if (enc == 2) {
          target += 1;
        }
        else if (enc == -3) {
          target -= 10;
        }
        else if (enc == 3) {
          target += 10;
        }
        else if (enc < 0) {
          target -= 20;
        }
        else {
          target += 20;
        }
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
      else if (buttonCount < MODE_SET_MODE_COUNT) {
        mode |= MODE_SHOW;
      }
      else {
        mode &= ~(MODE_SET | MODE_SHOW);
        if (mode & MODE_ON) {
          if (temp < target) {
            HEAT_PORT |= HEAT_PIN;
          }
          else {
            HEAT_PORT &= ~HEAT_PIN;
            if (mode & MODE_HIT) {
              mode &= ~MODE_ON;
              targetHit = true;
            }
          }
        }
      }
    }

    // set the display and status LEDs
    if (mode & MODE_ON) {
      LED_PORT = (LED_PORT & ~LED_MASK) | LED_START;
    }
    else {
      LED_PORT = (LED_PORT & ~LED_MASK) | LED_STOP;
    }
    // error is first priority, then set, then value
    if (mode & MODE_ERR) {
      char e[5] = {'e', 'r', 'r', '0', '\0'};
      disp.set(e, 4);
    }
    else if (mode & MODE_SET) {
      disp.set(s, sLen);
    }
    else if (mode & MODE_SHOW) {
      if (mode & MODE_HIT) {
        char e[4] = {'h', 'i', 't', '\0'};
        disp.set(e, 3); 
      }
      else {
        char e[5] = {'h', 'o', 'l', 'd', '\0'};
        disp.set(e, 4); 
      }
    }
    else {
      disp.set(d, dLen);
    }
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
  ADCSRA = ( (1<<ADPS2) | (1<<ADPS1) );
  // enable ADC, do a reading, and toss it
  ADCSRA |= ( (1<<ADEN) | (1<<ADSC) );
  // wait for conversion to complete
  while (ADCSRA & (1<<ADSC));
  // read the value;
  uint16_t read = ADCL | (ADCH << 8);
  (void) read;
}
