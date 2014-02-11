// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: buttons.h
// description: header for push-button input class

#ifndef REFLOW_BUTTONS_H
#define REFLOW_BUTTONS_H

// typedefs
#include <stdint.h>

#define BUTTON_DEBOUNCE_COUNT  3
#define BUTTON_HOLD_COUNT      50

class Buttons {
public:
  // contructor - gives private variables default values
  Buttons(void);

  // get the flag states and clear as necessary
  bool getPress(uint8_t *s);
  bool getHold(uint8_t *s);

  // handle debouncing
  void handleTimer(void);

  // initialization
  void init(void);
private:
  // get button state
  uint8_t getState(void);

  // init switch pins as inputs with pullups enabled
  void initPins(void);
  // init timer for debouncing
  void initTimer(void);

  // interrupt helpers
  void enableTimer(void);
  void disableTimer(void);

  // ISR volatiles
  // button states
  uint8_t state;
  uint8_t lastState;
  uint8_t pressState;
  // switch timer counter
  uint8_t timerCount;
  // switch event flags
  bool release;
  bool press;
  bool hold;
};

#endif