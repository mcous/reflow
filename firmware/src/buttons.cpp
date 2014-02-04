// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: buttons.cpp
// description: class for push-button input

#include "buttons.h"
#include "pindefs.h"

// contructor - gives private variables default values
Buttons::Buttons(void) {
  // switch states
  state = BUTTON_MASK;
  pressState = BUTTON_MASK;
  // switch timer counter
  timerCount = 0;
  // switch event flags
  release = false;
  press = false;
}

// handle debouncing the pins and sensing presses vs holds
void Buttons::handleTimer(void) {
  // disable the timer
  disableTimer();
  // save the old state and read in the new one
  lastState = state;
  state = getState();
  // compare and increment count if they match
  if( state == lastState ) {
    timerCount++;
  }
  else {
    timerCount = 0;
  }
  // after 3 matches, consider switch debounced
  if (timerCount >= BUTTON_DEBOUNCE_COUNT) {
    // if all switches are up, it's a release
    if ( state == BUTTON_MASK ) {
      release = true;
      timerCount = 0;
    }
    else {
      // else it's not a release
      release = false;
      press = true;
      pressState = state & 0x0F;
      // after INPUT_HOLD_COUNT, start faking releases
      //if (timerCount > INPUT_HOLD_COUNT) {
      //  release = true;
      //  timerCount = INPUT_REPEAT_COUNT;
      //}
    }
  }
  // re-enable the timer
  enableTimer();
}


// initialization
void Buttons::init(void) {
  initPins();
  initTimer();
  enableTimer();
}

// get switch state
uint8_t Buttons::getState(void) {
  return PIN(BUTTON_PORT) & BUTTON_MASK;
}

// get the flag states and clear as necessary
// set uint8_t at pointer to switch state if flag is true
// outputted switch state is bit flipped for convenience in the app
bool Buttons::getPress(uint8_t *s) {
  if (press && release) {
    press = false;
    release = false;
    *s = BUTTON_MASK & ~pressState;
    return true;
  }
  return false;
}

// init switch pins as inputs with pullups enabled
void Buttons::initPins(void) {
  // clear pins in DDR to inputs
  DDR(BUTTON_PORT) &= ~BUTTON_MASK;
  // enable pull up resistors
  BUTTON_PORT |= BUTTON_MASK;
}

// init timer for debouncing
// using an 8-bit timer on an 8MHz clock
// PS=1024 means an overflow will occur after about 32 ms
void Buttons::initTimer(void) {
  // ensure timer2 settings are cleared out
  TCCR2A = 0;
  // set prescaler to 1024
  TCCR2B = ( (1 << CS22) | (1<<CS21) | (1 << CS20) );
}

void Buttons::enableTimer(void) {
  // reload timer to 156 to get overflow to occur closer to every 12 ms
  TCNT2 = 156;
  // enable the overflow interrupt
  TIMSK2 = (1 << TOIE2);
}

void Buttons::disableTimer(void) {
  TIMSK2 = 0;
}