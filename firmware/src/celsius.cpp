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

// set to a temperature in celsius or farenheit
void Celsius::set(int16_t t, uint8_t units) {
  if (units == TEMP_UNITS_C) {
    set(t);
  }
  else {

  }
}

void Celsius::setScaled(int16_t c, uint8_t power) {
  // scale c so it matches 4*temp
  int8_t diff = TEMP_POWER - power;
  if (diff > 0) {
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
