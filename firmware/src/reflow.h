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

// operating modes
#define MODE_OFF  0
#define MODE_ON   1
#define MODE_SET  2

// global objects
// button and rotary encoder input
Buttons b;
Encoder e;
// voltage reference
float vref;

// function prototypes
int main(void);
// initialize LEDs
void initLeds(void);
// intialize heater
void initHeat(void);
// intialize thermocouple reading
void initThermo(void);
// read the thermocouple
float readThermo(void);

#endif