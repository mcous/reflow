// reflow
// Copyright 2014 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: celcius.cpp
// description: temperature in celcius class

#include "celcius.h"

// public constructor
// initializes temperature to 0
Celcius::Celcius(void) {
  celcius = 0;
}

// temperature setter
void Celcius::set(int16_t c) {
  setScaled(c, 0);
}

// set to a temperature in celcius or farenheit
void set(int16_t t, uint8_t units) {
  if (units == TEMP_UNITS_C) {
    set(t);
  }
  else {
    
  }
}

void Celcius::setScaled(int16_t c, uint8_t power) {
  // scale c so it matches 4*temp
  int8_t diff = TEMP_POWER - power;
  if (diff > 0) {
    c <<= diff;
  }
  else {
    c >>= -diff;
  }
  celcius = c;
}

// temperature getter
int16_t Celcius::getScaled(void) {
  return celcius;
}
