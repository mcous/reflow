// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: celcius.h
// description: header for temperature in celcius class

#ifndef REFLOW_CELCIUS_H
#define REFLOW_CELCIUS_H

#include <stdint.h>

class Celcius {
public:
  // public constructor
  Celcius(void);
  // temperature setters
  // set to a temperature in celcius
  void set(int16_t c);
  // set the temperature with an int that is a power of 2 multiple of the temperature
  // c is the integer
  // power is the power of two by which the int is scaled
  // example - c=200, power=1 will set the temperature to 100
  void setScaled(int16_t c, uint8_t power);
  
  // temperature getter
  // returns the internal representation (i.e. 4*celcius)
  int16_t getScaled(void);

  // declare that boolean operators are friends
  friend bool operator==(const Celcius& lhs, const Celcius& rhs);
  friend bool operator!=(const Celcius& lhs, const Celcius& rhs);
  friend bool operator< (const Celcius& lhs, const Celcius& rhs);
  friend bool operator> (const Celcius& lhs, const Celcius& rhs);
  friend bool operator<=(const Celcius& lhs, const Celcius& rhs);
  friend bool operator>=(const Celcius& lhs, const Celcius& rhs);

private:
  // signed 16-bit int to hold the temperature
  // internal representation is 4x the temperature
  // this gives us 0.25 degree resolution in an int
  int16_t celcius;
};


// time to overload some opperators
// gonna need the comparison operators
inline bool operator==(const Celcius& lhs, const Celcius& rhs){return (lhs.celcius == rhs.celcius); }
inline bool operator!=(const Celcius& lhs, const Celcius& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Celcius& lhs, const Celcius& rhs){return (lhs.celcius < rhs.celcius); }
inline bool operator> (const Celcius& lhs, const Celcius& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Celcius& lhs, const Celcius& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Celcius& lhs, const Celcius& rhs){return !operator< (lhs,rhs);}
// and probably addition and subtraction would be useful

#endif