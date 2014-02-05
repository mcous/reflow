// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: display.cpp
// description: class for 4x 7-segment + decimal point display

#include "display.h"

// contructor
Display::Display(void) {
  /*
  // intialize the font array
  // put this shit in program memory when you get around to it
  font[0] = ( DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F );
  font[1] = ( DISPLAY_SEG_B | DISPLAY_SEG_C );
  font[2] = ( DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_G | DISPLAY_SEG_E | DISPLAY_SEG_D );
  font[3] = ( DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_G | DISPLAY_SEG_C | DISPLAY_SEG_D );
  font[4] = ( DISPLAY_SEG_F | DISPLAY_SEG_G | DISPLAY_SEG_B | DISPLAY_SEG_C );
  font[5] = ( DISPLAY_SEG_A | DISPLAY_SEG_F | DISPLAY_SEG_G | DISPLAY_SEG_C | DISPLAY_SEG_D );
  font[6] = ( DISPLAY_SEG_A | DISPLAY_SEG_F | DISPLAY_SEG_E | DISPLAY_SEG_D | DISPLAY_SEG_C | DISPLAY_SEG_G );
  font[7] = ( DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C );
  font[8] = ( DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G );
  font[9] = ( DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G );
  // error
  // e
  font[10] = ( DISPLAY_SEG_A | DISPLAY_SEG_F | DISPLAY_SEG_G | DISPLAY_SEG_E | DISPLAY_SEG_D );
  // r
  font[11] = ( DISPLAY_SEG_G | DISPLAY_SEG_E );
  */
  // decimal point
  dp = DISPLAY_SEG_OFF;

  // all digits off
  digit = 0;
  for (uint8_t i=0; i<DISPLAY_NUM_DIGITS; i++) {
    digDisp[i] = 0;
  }
}

// public set function
void Display::set(float num) {
  // whole digit places
  uint8_t thouth = ((uint16_t)(num*1000)%10);
  uint8_t hundth = ((uint16_t)(num*100)%10);
  uint8_t tenth  = ((uint16_t)(num*10)%10);
  uint8_t one    = ((uint16_t)(num))%10;
  uint8_t ten    = ((uint16_t)(num/10)%10);
  uint8_t hund   = ((uint16_t)(num/100)%10);
  uint8_t thou   = ((uint16_t)(num/1000)%10);

  // three decimal points
  if (num < 10) {
    dp = 0;
    digDisp[0] = one;
    digDisp[1] = tenth;
    digDisp[2] = hundth;
    digDisp[3] = thouth;
  }
  // two decimal points
  else if (num < 100) {
    dp = 1;
    digDisp[0] = ten;
    digDisp[1] = one;
    digDisp[2] = tenth;
    digDisp[3] = hundth;
  }
  // one decimal point
  else if (num < 1000) {
    dp = 2;
    digDisp[0] = hund;
    digDisp[1] = ten;
    digDisp[2] = one;
    digDisp[3] = tenth;
  }
  // no decimal points
  else {
    dp = 3;
    digDisp[0] = thou;
    digDisp[1] = hund;
    digDisp[2] = ten;
    digDisp[3] = one;
  }

  return;
}

// set display error
void Display::setErr(uint8_t err) {
  dp = DISPLAY_SEG_OFF;
  digDisp[0] = 10;
  digDisp[1] = 11;
  digDisp[2] = 11;
  digDisp[3] = err;
}

void Display::refresh(void) {
  // increment or overflow
  digit = (digit>=DISPLAY_NUM_DIGITS-1) ? 0 : digit+1;
  // enable the digit
  DISPLAY_DIG_PORT = (DISPLAY_DIG_PORT & ~DISPLAY_DIG_MASK) | (1<<digit);
  DISPLAY_SEG_PORT = font[digDisp[digit]];
  // decimal point if necessary
  if (digit == dp) {
    DISPLAY_SEG_PORT |= DISPLAY_SEG_DP;
  }

  return;
}

void Display::init(void) {
  // set digit control to output and initialize at off
  DDR(DISPLAY_DIG_PORT) |= DISPLAY_DIG_MASK;
  DISPLAY_DIG_PORT &= ~DISPLAY_DIG_MASK;

  // set segment control to output and initialize at off
  DDR(DISPLAY_SEG_PORT) |= DISPLAY_SEG_MASK;
  DISPLAY_SEG_PORT &= ~DISPLAY_SEG_MASK;

  return;
}

// retrieve characters from fontset
uint8_t Display::getChar(char c) {
  // numbers
  if (c >= '0' && c <= '9') {
    c -= '0';
  }
  // upper case letters
  else if (c >= 'A' && c <= 'Z') {
    c -= ('A'-10);
  }
  // lowercase letters
  else if (c >= 'a' && c <= 'z') {
    c -= ('a'-10);
  }
  // anything else
  else {
    // return a space
    return 0;
  }

  return pgm_read_byte(&(font[(uint8_t)(c)]));
}

// character representations
// array contains 0-9, A-Z
const uint8_t Display::font[] PROGMEM = {
  // 0
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F),
  // 1
  (DISPLAY_SEG_B | DISPLAY_SEG_C),
  // 2
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G),
  // 3
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_G),
  // 4
  (DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // 5
  (DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // 6
  (DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // 7
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C),
  // 8
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // 9
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // A
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // B
  (DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // C
  (DISPLAY_SEG_A | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F),
  // D
  (DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G),
  // E
  (DISPLAY_SEG_A | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // F
  (DISPLAY_SEG_A | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // G
  (DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F),
  // H
  (DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // I
  (DISPLAY_SEG_E | DISPLAY_SEG_F),
  // J
  (DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E),
  // K
  (DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // L
  (DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F),
  // M
  (DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_E),
  // N
  (DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_E),
  // O
  (DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G),
  // P
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // Q
  (DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // R
  (DISPLAY_SEG_E | DISPLAY_SEG_G),
  // S
  (DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // T
  (DISPLAY_SEG_A | DISPLAY_SEG_E | DISPLAY_SEG_F),
  // U
  (DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E),
  // V
  (DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F),
  // W
  (DISPLAY_SEG_B | DISPLAY_SEG_D | DISPLAY_SEG_F),
  // X
  (DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // Y
  (DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G),
  // Z
  (DISPLAY_SEG_A | DISPLAY_SEG_D | DISPLAY_SEG_G)
};