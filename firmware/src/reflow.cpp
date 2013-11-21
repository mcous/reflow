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
  // get the input ready
  b.init();

  uint8_t loop = 0;
  float num = 0;

  // enable global interrupts
  sei();

  // sideways eight loop
  for (;;) {
    // set the display
    disp.set(num);
    // refresh the display
    disp.refresh();

    // handle buttons
    uint8_t buttons;
    // presses
    if (b.getPress(&buttons)) {
      if (buttons == BUTTON_SET) {
        num += 10;
      } 
      else if (buttons == BUTTON_START) {
        num += 20;
      }
      else {
        num += 30;
      }
    }
    // holds
    if (b.getHold(&buttons)) {
      // do nothing
      break;
    }

    // increment the counter
    loop++;
    if (loop > 10) {
      num+=0.001;
      loop = 0;
      if (num >= 10000) {
        num = 0;
      }
    }

    // slight delay
    _delay_ms(2);

  }

  // DEEP THOUGHT
  return 42;
}