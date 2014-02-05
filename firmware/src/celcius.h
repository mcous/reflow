// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: celcius.h
// description: header for temperature in celcius class

#ifndef REFLOW_CELCIUS_H
#define REFLOW_CELCIUS_H

#include <stdint.h>

class Celcius {
public:
  // public constructor
  Celcius(void);
  // temperature setter
  void set(int16_t c);
  // temperature getter
  int16_t get(void);
private:
  // signed 16-bit int to hold the temperature
  int16_t celcius;
};

#endif