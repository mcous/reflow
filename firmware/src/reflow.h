// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: reflow.h
// description: header file for the reflow oven application

#ifndef REFLOW_H
#define REFLOW_H

// necessary application includes
#include "encoder.h"

// operating modes
#define MODE_OFF   0x00
#define MODE_ON    0x01
#define MODE_SET   0x02
#define MODE_HOLD  0x04
#define MODE_HIT   0x08
#define MODE_SHOW  0x10
#define MODE_ERR   0x80

// timing for set mode
#define MODE_SET_DISPLAY_COUNT  16
#define MODE_SET_MODE_COUNT     64

// application events
#define REFLOW_EVENT_vect TIMER1_COMPA_vect
#define REFLOW_EVENT_MAX  0x1FF
// assuming timer running at 512 Hz
// refresh the display at 256 Hz
#define REFLOW_DISPLAY_FLAG   0x1
#define REFLOW_DISPLAY_EVENT  0x1
// poll the buttons at 64 Hz
#define REFLOW_BUTTON_FLAG   0x2
#define REFLOW_BUTTON_EVENT  0x7
//read the encoder at 8 Hz
#define REFLOW_ENCODER_FLAG  0x4
#define REFLOW_ENCODER_EVENT  0x3F
// check the temperature at 2 Hz
#define REFLOW_THERMO_FLAG   0x8
#define REFLOW_THERMO_EVENT   0xFF

// error codes
#define ERROR_THERMO_OPEN 0

// voltage reference (probably not this exactly but it's good enough)
#define VREF  5

// global objects
// rotary encoder input
Encoder e;

// ISR volatiles
volatile uint16_t adcRead;
//volatile bool tempCheck;
volatile uint16_t eventTimer;
volatile uint8_t eventFlags;

// function prototypes
int main(void);

// events
// enable the event timer
void enableEventTimer(void);

// initialization functions
// initialize LEDs
void initLeds(void);
// intialize heater
void initHeat(void);
// intialize thermocouple reading
void initThermo(void);

// read the thermocouple
// returns the temperature in a Celsius object
//Celsius readThermo(void);

#endif