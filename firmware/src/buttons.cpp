// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: input.h
// description: class for push-button and rotary encoder input

#include "buttons.h"
#include "pindefs.h"

// contructor - gives private variables default values
Buttons::Buttons(void) {
  // switch states
  state = BUTTON_MASK;
  pressState = BUTTON_MASK;
  holdState = BUTTON_MASK;
  // switch timer counter
  timerCount = 0;
  // switch event flags
  release = false;
  press = false;
  hold = false;
}

// handle button pin change
void Buttons::handleChange(void) {
  // disable the timer and switch interrupts and reset the switch timer counter
  disableTimer();
  disableInt();
  timerCount = 0;
  // save the state that triggered the interrupt
  state = getState();
  // start the switch timer to debounce and time if necessary
  enableTimer();
}

// handle debouncing the pins and sensing presses vs holds
void Buttons::handleTimer(void) {
  // disable the timer
  disableTimer();
  // increment the counter
  timerCount++;
  // clear the release flag
  release = false;

  // check the values still match (i.e. if true, it wasn't a bounce)
  if (getState() == state) {
    // if one or both switches are down (if both switches are up, both will read high)
    if ( state != BUTTON_MASK) {
      // check for a press
      if (timerCount == 1) {
        press = true;
        pressState = state;
      }
      // check for a hold
      else if (timerCount >= BUTTON_HOLD_COUNT) {
        press = false;
        hold = true;
        holdState = state;
        timerCount = 1;
      }
      // re-enable the timer
      enableTimer();
    }
    // else switches were released
    else {
      release = true;
    }
  }

  // re-enable the pin change interrupt
  enableInt();
}


// initialization
void Buttons::init(void) {
  initPins();
  initInt();
  initTimer();
  enableInt();
}

// get switch state
uint8_t Buttons::getState(void) {
  return PIN(BUTTON_PORT) & BUTTON_MASK;
}

// get the flag states and clear as necessary
// set uint8_t at pointer to switch state if flag is true
// outputted switch state is bit flipped for convenience in the app
bool Buttons::getHold(uint8_t *s) {
  if (hold) {
    hold = false;
    *s = BUTTON_MASK & ~holdState;
    return true;
  }
  return false;
}

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

// init pin change interrupts
void Buttons::initInt(void) {
  // set up pin change interrupt on the pins
  BUTTON_PCMSK |= BUTTON_MASK;
}

// init timer for debouncing
// using an 8-bit timer on an 8MHz clock
// PS=1024 means an overflow will occur after about 32 ms
void Buttons::initTimer(void) {
  // ensure timer2 settings are cleared out
  TCCR2A = 0;
  // set prescaler to 1024
  TCCR2B = ( (1 << CS22) | (1 << CS21) | (1 << CS20) );
}

// interrupt helpers
void Buttons::enableInt(void) {
  // enable the pin change interrupt
  PCICR |= BUTTON_PCIE;
}

void Buttons::disableInt(void) {
  // disable the pin change interrupt
  PCICR &= ~BUTTON_PCIE;
}

void Buttons::enableTimer(void) {
  // reload timer
  TCNT2 = 0;
  // enable the overflow interrupt
  TIMSK2 = (1 << TOIE2);
}

void Buttons::disableTimer(void) {
  TIMSK2 = 0;
}