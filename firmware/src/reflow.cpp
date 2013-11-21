// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: reflow.cpp
// description: application file for the reflow oven controller

#include <avr/io.h>
#include <util/delay.h>
#include "reflow.h"
#include "display.h"

// application main method
int main(void) {

  // get the display ready
  Display disp;
  disp.init();

  uint8_t loop = 0;
  float num = 0;
  // sideways eight loop
  for (;;) {
    // set the display
    disp.set(num);
    // refresh the display
    disp.refresh();

    //DISPLAY_DIG_PORT = (DISPLAY_DIG_PORT & ~DISPLAY_DIG_MASK) | (1<<2);
    //DISPLAY_SEG_PORT = disp.font[0];

    // increment
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