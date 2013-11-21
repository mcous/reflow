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