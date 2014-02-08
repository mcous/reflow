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
#include <avr/pgmspace.h>
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
  //void set(float num);
  // set display error
  //void setErr(uint8_t err);
  // set the display given a string
  void set(char *s, uint8_t strLen);
  // refresh display
  void refresh(void);
  // new refresh function
  // based on font file with characters saved as 0b0GFEDCBA
  //void newRefresh(void);
  // initialize display
  void init(void);

private:
  // font set
  const static uint8_t font[37] PROGMEM;
  // retriece character from the font set
  uint8_t getChar(char c);
  // current digit
  uint8_t digit;
  // current display for the digits
  uint8_t digDisp[DISPLAY_NUM_DIGITS];
  // decimal point
  //uint8_t dp;
};

#endif
