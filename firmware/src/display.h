// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: display.h
// description: header for 7-segment + decimal point display class

#ifndef REFLOW_DISPLAY_H
#define REFLOW_DISPLAY_H

// class includes
#include <avr/io.h>
#include "pindefs.h"

// defines
// number of digits
#define DISPLAY_NUM_DIGITS 4
// decimal point off
#define DISPLAY_DIG_OFF 0xFF



class Display {
public:
  // constructor
  Display(void);
  // set display
  void set(float num);
  // refresh display
  void refresh();
  // initialize display
  void init();

//private:
  // font set
  uint8_t font[10];
  // current digit
  uint8_t digit;
  // current display for the digits
  uint8_t digDisp[DISPLAY_NUM_DIGITS];
  // decimal point
  uint8_t dp;

};

#endif