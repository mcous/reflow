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
  //dp = DISPLAY_SEG_OFF;

  // all digits off
  digit = 0;
  for (uint8_t i=0; i<DISPLAY_NUM_DIGITS; i++) {
    digDisp[i] = 0;
  }
}

/*
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
*/

// set display error
// void Display::setErr(uint8_t err) {
//   err += '0';
//   char e[4] = {'e', 'r', 'r', (char)err};
//   set(e, 4);
// }

void Display::set(char *s, uint8_t strLen) {
  // segments holder
  uint8_t segs;
  // string index counter
  uint8_t i=0;
  // digit display counter
  uint8_t j=DISPLAY_NUM_DIGITS;
  // loop through the string
  do {
    if (s[i] != '.') {
      uint8_t d = getChar(s[i]);
      segs = 0;
      // convert 0b0GFDECBA to pins
      // sorry, just went with an unrolled loop because life is hell
      // also the hardware is changing so this code won't live long
      // segment A
      if (d & 0x1) {
        segs |= DISPLAY_SEG_A;
      }
      // segment B
      if (d & 0x2) {
        segs |= DISPLAY_SEG_B;
      }
      // segment C
      if (d & 0x4) {
        segs |= DISPLAY_SEG_C;
      }
      // segment D
      if (d & 0x8) {
        segs |= DISPLAY_SEG_D;
      }
      // segment E
      if (d & 0x10) {
        segs |= DISPLAY_SEG_E;
      }
      // segment F
      if (d & 0x20) {
        segs |= DISPLAY_SEG_F;
      }
      // segment G
      if (d & 0x40) {
        segs |= DISPLAY_SEG_G;
      }
      digDisp[j-1] = segs;
      j--;
    }
    else {
      // put a decimal on the previous digit
      digDisp[j] |= DISPLAY_SEG_DP;
    }
    i++;
  } while (j > 0 && i < strLen);

  // blank the rest
  while (j > 0) {
    digDisp[j-1] = 0;
    j--;
  }
  // right justify
  // implement later
}

// void Display::refresh(void) {
//   // increment or overflow
//   digit = (digit>=DISPLAY_NUM_DIGITS-1) ? 0 : digit+1;
//   // rearrange
//   uint8_t d = getChar('0'+digDisp[digit]);
//   uint8_t segs = 0;
//   if (d & 0x1) {
//     segs |= DISPLAY_SEG_A;
//   }
//   // segment B
//   if (d & 0x2) {
//     segs |= DISPLAY_SEG_B;
//   }
//   // segment C
//   if (d & 0x4) {
//     segs |= DISPLAY_SEG_C;
//   }
//   // segment D
//   if (d & 0x8) {
//     segs |= DISPLAY_SEG_D;
//   }
//   // segment E
//   if (d & 0x10) {
//     segs |= DISPLAY_SEG_E;
//   }
//   // segment F
//   if (d & 0x20) {
//     segs |= DISPLAY_SEG_F;
//   }
//   // segment G
//   if (d & 0x40) {
//     segs |= DISPLAY_SEG_G;
//   }
//   digDisp[digit] = segs;
//   // enable the digit
//   DISPLAY_DIG_PORT = (DISPLAY_DIG_PORT & ~DISPLAY_DIG_MASK) | (1<<digit);
//   DISPLAY_SEG_PORT = segs;
//   // decimal point if necessary
//   if (digit == dp) {
//     DISPLAY_SEG_PORT |= DISPLAY_SEG_DP;
//   }
//   return;
// }

void Display::refresh(void) {
  // increment or overflow
  digit = (digit>=DISPLAY_NUM_DIGITS-1) ? 0 : digit+1;
  // digit 0 is the LSD, digit 3 is the MSD
  DISPLAY_DIG_PORT = (DISPLAY_DIG_PORT & ~DISPLAY_DIG_MASK) | (1<<(DISPLAY_NUM_DIGITS-digit-1));
  // write the digits to the PORT
  DISPLAY_SEG_PORT = digDisp[digit];
  // done
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
  // dash
  else if (c == '-') {
    c = 36;
  }
  // anything else
  else {
    // return a space
    return 0;
  }

  return pgm_read_byte(&(font[(uint8_t)(c)]));
}

// character representations
// array contains '0'-'9', 'A'-'Z', '-'
const uint8_t Display::font[] PROGMEM = {
  // 0 - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F
  0x3F,
  // 1 - DISPLAY_SEG_B | DISPLAY_SEG_C
  0x06,
  // 2 - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G
  0x5B,
  // 3 - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_G
  0x4F,
  // 4 - DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x66,
  // 5 - DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x6D,
  // 6 - DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x7D,
  // 7 - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C
  0x07,
  // 8 - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x7F,
  // 9 - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x6F,
  // A - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x77,
  // B - DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x7C,
  // C - DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G
  0x58,
  // D - DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G
  0x5E,
  // E - DISPLAY_SEG_A | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x79,
  // F - DISPLAY_SEG_A | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x71,
  // G - DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F
  0x3D,
  // H - DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x74,
  // I - DISPLAY_SEG_E | DISPLAY_SEG_F
  0x30,
  // J - DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E
  0x1E,
  // K - DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x76,
  // L - DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F
  0x38,
  // M - DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_E
  0x15,
  // N - DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_G
  0x54,
  // O - DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G
  0x5C,
  // P - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x73,
  // Q - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x67,
  // R - DISPLAY_SEG_E | DISPLAY_SEG_G
  0x50,
  // S - DISPLAY_SEG_A | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x6D,
  // T - DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x78,
  // U - DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_F
  0x3E,
  // V - DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_E
  0x1C,
  // W - DISPLAY_SEG_B | DISPLAY_SEG_D | DISPLAY_SEG_F
  0x2A,
  // X - DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_E | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x76,
  // Y - DISPLAY_SEG_B | DISPLAY_SEG_C | DISPLAY_SEG_D | DISPLAY_SEG_F | DISPLAY_SEG_G
  0x6E,
  // Z - DISPLAY_SEG_A | DISPLAY_SEG_B | DISPLAY_SEG_D | DISPLAY_SEG_E | DISPLAY_SEG_G
  0x5B,
  // dash - DISPLAY_SEG_G
  0x40
};