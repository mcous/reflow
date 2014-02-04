// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: encoder.h
// description: header for rotary encoder input class

#ifndef REFLOW_ENCODER_H
#define REFLOW_ENCODER_H

#include <stdint.h>
#include <avr/pgmspace.h>

class Encoder {
public:
  // contructor
  Encoder(void);
  // initialization of pins and interrupts
  void init(void);
  // get rotation since last check
  int8_t getChange(void);
  // handle the pin change interrupt
  void handleChange(void);
private:
  // transition lookup table
  static const int8_t trans[16] PROGMEM;
  // variable to hold state
  volatile uint8_t state;
  // location of rotation
  volatile int8_t loc;
  // ticks (4 ticks per location)
  volatile int8_t tick;
  // get encoder state
  uint8_t getState(void);
  // initialize pins and pullups
  void initPins(void);
  // initialize pin change interrupts
  void initInt(void);
};

#endif