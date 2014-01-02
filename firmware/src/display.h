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
#define DISPLAY_SEG_OFF 0xFF

class Display {
public:
  // constructor
  Display(void);
  // set display
  void set(float num);
  // set display error
  void setErr(uint8_t err);
  // refresh display
  void refresh(void);
  // initialize display
  void init(void);

private:
  // font set
  uint8_t font[12];
  // current digit
  uint8_t digit;
  // current display for the digits
  uint8_t digDisp[DISPLAY_NUM_DIGITS];
  // decimal point
  uint8_t dp;
};

#endif
