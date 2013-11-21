// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: input.h
// description: class for push-button and rotary encoder input

#include "input.h"
#include "pindefs.h"

// contructor - gives private variables default values
Input::Input(void) {
  // switch states
  buttonState = INPUT_BUTTON_MASK;
  buttonPressState = INPUT_BUTTON_MASK;
  buttonHoldState = INPUT_BUTTON_MASK;
  // switch timer counter
  buttonTimerCount = 0;
  // switch event flags
  buttonRelease = false;
  buttonPress = false;
  buttonHold = false;
}

// handle button pin change
void Input::handleButtonChange(void) {
  // disable the timer and switch interrupts and reset the switch timer counter
  disableButtonTimer();
  disableButtonInt();
  buttonTimerCount = 0;
  // save the state that triggered the interrupt
  buttonState = getButtonState();
  // start the switch timer to debounce and time if necessary
  enableButtonTimer();
}

// handle debouncing the pins and sensing presses vs holds
void Input::handleButtonTimer(void) {
  // disable the timer
  disableButtonTimer();
  // increment the counter
  buttonTimerCount++;
  // clear the release flag
  buttonRelease = false;

  // check the values still match (i.e. if true, it wasn't a bounce)
  if (getButtonState() == buttonState) {
    // if one or both switches are down (if both switches are up, both will read high)
    if ( buttonState != INPUT_BUTTON_MASK) {
      // check for a press
      if (buttonTimerCount == 1) {
        buttonPress = true;
        buttonPressState = buttonState;
      }
      // check for a hold
      else if (buttonTimerCount >= INPUT_BUTTON_HOLD_COUNT) {
        buttonPress = false;
        buttonHold = true;
        buttonHoldState = buttonState;
        buttonTimerCount = 1;
      }
      // re-enable the timer
      enableButtonTimer();
    }
    // else switches were released
    else {
      buttonRelease = true;
    }
  }

  // re-enable the pin change interrupt
  enableButtonInt();
}


// initialization
void Input::init(void) {
  initButtonPins();
  initButtonInt();
  initButtonTimer();
  enableButtonInt();
}

// get switch state
uint8_t Input::getButtonState(void) {
  return PIN(INPUT_BUTTON_PORT) & INPUT_BUTTON_MASK;
}

// get the flag states and clear as necessary
// set uint8_t at pointer to switch state if flag is true
// outputted switch state is bit flipped for convenience in the app
bool Input::getButtonHold(uint8_t *s) {
  if (buttonHold) {
    buttonHold = false;
    *s = INPUT_BUTTON_MASK & ~buttonHoldState;
    return true;
  }
  return false;
}

bool Input::getButtonPress(uint8_t *s) {
  if (buttonPress && buttonRelease) {
    buttonPress = false;
    buttonRelease = false;
    *s = INPUT_BUTTON_MASK & ~buttonPressState;
    return true;
  }
  return false;
}

// init switch pins as inputs with pullups enabled
void Input::initButtonPins(void) {
  // clear pins in DDR to inputs
  DDR(INPUT_BUTTON_PORT) &= ~INPUT_BUTTON_MASK;
  // enable pull up resistors
  INPUT_BUTTON_PORT |= INPUT_BUTTON_MASK;
}

// init pin change interrupts
void Input::initButtonInt(void) {
  // set up pin change interrupt on the pins
  INPUT_BUTTON_PCMSK |= INPUT_BUTTON_MASK;
}

// init timer for debouncing
// using an 8-bit timer on an 8MHz clock
// PS=1024 means an overflow will occur after about 32 ms
void Input::initButtonTimer(void) {
  // ensure timer2 settings are cleared out
  TCCR2A = 0;
  // set prescaler to 1024
  TCCR2B = ( (1 << CS22) | (1 << CS21) | (1 << CS20) );
}

// interrupt helpers
void Input::enableButtonInt(void) {
  // enable the pin change interrupt
  PCICR |= INPUT_BUTTON_PCIE;
}

void Input::disableButtonInt(void) {
  // disable the pin change interrupt
  PCICR &= ~INPUT_BUTTON_PCIE;
}

void Input::enableButtonTimer(void) {
  // reload timer
  TCNT2 = 0;
  // enable the overflow interrupt
  TIMSK2 = (1 << TOIE2);
}

void Input::disableButtonTimer(void) {
  TIMSK2 = 0;
}