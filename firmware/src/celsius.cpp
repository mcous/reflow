// reflow
// Copyright 2014 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: celsius.cpp
// description: temperature in celsius class

#include "celsius.h"

// public constructor
// initializes temperature to 0
Celsius::Celsius(void) {
  celsius = 0;
}

// temperature setter
void Celsius::set(int16_t c) {
  setScaled(c, 0);
}

void Celsius::setScaled(int16_t c, uint8_t power) {
  // scale c so it matches 4*temp
  int8_t diff = TEMP_POWER - power;
  if (diff >= 0) {
    c <<= diff;
  }
  else {
    c >>= -diff;
  }
  celsius = c;
}

// temperature getter
int16_t Celsius::getScaled(void) {
  return celsius;
}

// convert temperature to string
// return number of chars written to buffer
uint8_t Celsius::toString(char *t) {
  int16_t c = celsius;
  bool foundDigit = false;
  uint8_t i = 0;

  // check for negative
  if (c < 0) {
    t[i++] = '-';
    c = -c;
  }

  // make sure first digit is '0'
  t[i] = '0';

  // thousands digit
  while (c >= 4000) {
    c -= 4000;
    t[i]++;
    foundDigit = true;
  }
  if (foundDigit) {
    t[++i] = '0';
  }

  // hundreds digit
  while (c >= 400) {
    c -= 400;
    t[i]++;
    foundDigit = true;
  }
  if (foundDigit) {
    t[++i] = '0';
  }

  // tens digit
  while (c >= 40) {
    c -= 40;
    t[i]++;
    foundDigit = true;
  }
  if (foundDigit) {
    t[++i] = '0';
  }

  // ones digit
  t[i++] = '0' + (c >> TEMP_POWER);
  // add a decimal point
  t[i++] ='.';
  // after the decimal
  if (c & 0x2) {
    t[i] = '5';
  }
  else {
    t[i] = '0';
  }

  return i+1;
}

// convert temperature to a string in a selected unit
// if farehnheit is selected, there will be no decimal point
uint8_t Celsius::toString(const uint8_t unit, char *t) {
  if (unit == TEMP_UNIT_F) {
    // get 10x the temperature in F
    //   F = C*9/5 + 32
    // 10F = C*9*2 + 320
    int16_t f = ((celsius*9) >> 1) + 320;
    bool foundDigit = false;
    uint8_t i = 0;

    // check for neg
    if (f < 0) {
      t[i++] = '-';
      f = -f;
    }

    // make sure first digit is '0'
    t[i] = '0';

    // thousands digit
    while (f >= 10000) {
      f -= 10000;
      t[i]++;
      foundDigit = true;
    }
    if (foundDigit) {
      t[++i] = '0';
    }

    // hundreds digit
    while (f >= 1000) {
      f -= 1000;
      t[i]++;
      foundDigit = true;
    }
    if (foundDigit) {
      t[++i] = '0';
    }

    // tens digit
    while (f >= 100) {
      f -= 100;
      t[i]++;
      foundDigit = true;
    }
    if (foundDigit) {
      t[++i] = '0';
    }

    // ones digit
    while (f >= 10) {
      f-= 10;
      t[i]++;
    }

    // put an F on the end
    t[++i] = 'F';
    
    return i+1;
  }
  else {
    return toString(t);
  }
}
