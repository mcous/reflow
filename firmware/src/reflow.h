// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: reflow.h
// description: header file for the reflow oven application

#ifndef REFLOW_H
#define REFLOW_H

// necessary includes
#include "buttons.h"
#include "encoder.h"
#include "celsius.h"

// operating modes
#define MODE_OFF  0
#define MODE_ON   1
#define MODE_SET  2
#define MODE_ERR  255

// error codes
#define ERROR_THERMO_OPEN 0

// voltage reference as measured externally
#define VREF  4.93

// global objects
// button and rotary encoder input
Buttons b;
Encoder e;

// ISR volatiles
volatile uint16_t adcRead;
volatile bool tempCheck;
//volatile int16_t tempFour;

// function prototypes
int main(void);
// initialize LEDs
void initLeds(void);
// intialize heater
void initHeat(void);
// intialize thermocouple reading
void initThermo(void);
// read the thermocouple
// returns the temperature in a Celsius object
Celsius readThermo(void);

#endif