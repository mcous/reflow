// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: input.h
// description: header for push-button and rotary encoder input class

#ifndef REFLOW_INPUT_H
#define REFLOW_INPUT_H

// typedefs
#include <stdint.h>

// timer counts
#define INPUT_BUTTON_HOLD_COUNT  35

// press or hold defines
#define INPUT_BUTTON_PRESS  0
#define INPUT_BUTTON_HOLD   1

class Input {
public:
  // contructor - gives private variables default values
  Input(void);

  // get the flag states and clear as necessary
  bool getButtonHold(uint8_t *s);
  bool getButtonPress(uint8_t *s);
  // handle pin change
  void handleButtonChange(void);
  // handle debouncing
  void handleButtonTimer(void);

  // disable the debounce timer and wait for a pin change (e.g. to exit a pin hold loop)
  void resetButtons(void);
  // initialization
  void init(void);
private:
    // get button state
  uint8_t getButtonState(void);

  // init switch pins as inputs with pullups enabled
  void initButtonPins(void);
  // init pin change interrupts
  void initButtonInt(void);
  // init timer for debouncing
  void initButtonTimer(void);

  // interrupt helpers
  void enableButtonInt(void);
  void disableButtonInt(void);
  void enableButtonTimer(void);
  void disableButtonTimer(void);

  // ISR volatiles
  // button states
  volatile uint8_t buttonState;
  volatile uint8_t buttonPressState;
  volatile uint8_t buttonHoldState;
  // switch timer counter
  volatile uint16_t buttonTimerCount;
  // switch event flags
  volatile bool buttonRelease;
  volatile bool buttonPress;
  volatile bool buttonHold;
};

#endif