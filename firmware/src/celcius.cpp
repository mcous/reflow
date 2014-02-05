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
  celcius = c;
}

// temperature getter
int16_t Celcius::get(void) {
  return celcius;
}
