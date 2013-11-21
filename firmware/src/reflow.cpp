// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: reflow.cpp
// description: application file for the reflow oven controller

#include <avr/io.h>
#include <util/delay.h>
#include "reflow.h"

// application main method
int main(void) {

  // set digit control as outputs and set to low (off)
  DDRC |= ( (1<<3) | (1<<2) | (1<<1) | (1<<0) );
  PORTC &= ~( (1<<3) | (1<<2) | (1<<1) | (1<<0) );
  // set segment control as outputs and set to low (off)
  DDRB = 0xFF;
  PORTB = 0;

  uint8_t dig = 0;
  // sideways eight loop
  for (;;) {
    // increment or overflow
    dig = (dig>3) ? 0 : dig + 1;
    // enable the digit
    PORTC = (PORTC & ~0x0F) | (1<<dig);
    // let's see what seg A is
    PORTB = (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0);
    // slight delay
    _delay_ms(2);
  }

  // DEEP THOUGHT
  return 42;
}