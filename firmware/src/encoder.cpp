// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: encoder.cpp
// description: class for rotary encoder input

#include "encoder.h"
#include "pindefs.h"

// contructor
Encoder::Encoder(void) {
  loc = 0;
  tick = 0;
  state = 0;
}

// encoder transition lookup table
const int8_t Encoder::trans[] PROGMEM = {
  0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0
};

// initialization of pins and interrupts
void Encoder::init(void) {
  initPins();
  state = getState();
  initInt();
}
 
// handle the pin change interrupt (preferably with aplomb) 
void Encoder::handleChange(void) {
  // shift the previous state over and pull in the new state
  state = (((state<<2) | getState()) & 0x0F);
  // increment or decrement the location with the lookup table
  tick += pgm_read_byte(&(trans[state]));
  if (tick > 3) {
    tick = 0;
    loc++;
  }
  else if (tick < -3) {
    tick = 0;
    loc--;
  }
}

// get rotation since last check
// clockwise = positive, counter-clockwise = negative
int8_t Encoder::getChange(void) {
  int8_t ret = loc;
  loc = 0;
  return ret;
}

// get encoder state
// returns 0000 00AB
uint8_t Encoder::getState(void) {
  // mask the encoder pins and shift for processing
  return ((PIN(ENCODER_PORT) & ENCODER_MASK) >> ENCODER_SHIFT);
}

// initialize pins and pullups
void Encoder::initPins(void) {
  // set pins to input
  DDR(ENCODER_PORT) &= ~ENCODER_MASK;
  // enable pullups
  ENCODER_PORT |= ENCODER_MASK;
}

// initialize pin change interrupts
void Encoder::initInt(void) {
  // set up pin change interrupt on the pins
  ENCODER_PCMSK |= ENCODER_MASK;
  // enable the interrupt
  PCICR |= ENCODER_PCIE;
}