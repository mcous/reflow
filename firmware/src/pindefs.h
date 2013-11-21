// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: pindefs.h
// description: pin definitions file for the reflow oven controller

#ifndef REFLOW_PINDEFS_H
#define REFLOW_PINDEFS_H

// include for AVR register addresses
#include <avr/io.h>

// DDR and PIN from port register macros
#define DDR(port) (*(&port-1))
#define PIN(port) (*(&port-2))

// display ports
#define DISPLAY_DIG_PORT  PORTC
#define DISPLAY_DIG_MASK  0x0F
#define DISPLAY_SEG_PORT  PORTB
#define DISPLAY_SEG_MASK  0xFF
// display segment pins
#define DISPLAY_SEG_A   (1<<0)
#define DISPLAY_SEG_B   (1<<7)
#define DISPLAY_SEG_C   (1<<2)
#define DISPLAY_SEG_D   (1<<4)
#define DISPLAY_SEG_E   (1<<5)
#define DISPLAY_SEG_F   (1<<6)
#define DISPLAY_SEG_G   (1<<1)
#define DISPLAY_SEG_DP  (1<<3)

// display pins


#endif