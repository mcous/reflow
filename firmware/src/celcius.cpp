// reflow
// Copyright 2014 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: celcius.cpp
// description: temperature in celcius class

#include "celcius.h"

// internal representation is the temp * 2^TEMP_POWER
// i.e. four times the temperature
#define TEMP_POWER 2

// public constructor
// initializes temperature to 0
Celcius::Celcius(void) {
  celcius = 0;
}

// temperature setter
void Celcius::set(int16_t c) {
  setScaled(c, 0);
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
