// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: pindefs.h
// description: pin definitions file for the reflow oven controller

#ifndef REFLOW_PINDEFS_H
#define REFLOW_PINDEFS_H

// include for AVR register addresses and interrupt vectors
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

// pushbutton port
#define BUTTON_PORT   PORTD
#define BUTTON_SET    (1<<4)
#define BUTTON_START  (1<<3)
#define BUTTON_STOP   (1<<2)
#define BUTTON_MASK   ( BUTTON_STOP | BUTTON_START | BUTTON_SET )
// pushbutton pin change stuff
#define BUTTON_PCIE        (1<<PCIE2)
#define BUTTON_PCMSK       PCMSK2
#define BUTTON_PCINT_vect  PCINT2_vect

// encoder port
#define ENCODER_PORT  PORTC
#define ENCODER_A     (1<<4)
#define ENCODER_B     (1<<5)
#define ENCODER_MASK  ( INPUT_ENC A | INPUT_ENC_B )
// encoder pin change
#define ENCODER_PCIE        (1<<PCIE1)
#define ENCODER_PCMSK       PCMSK1
#define ENCODER_PCINT_vect  PCINT1_vect


#endif