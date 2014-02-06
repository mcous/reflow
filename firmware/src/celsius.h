// reflow
// Copyright 2013 by Wiley Cousins, LLC.
// shared under the terms of the MIT License
//
// file: celsius.h
// description: header for temperature in celsius class

#ifndef REFLOW_CELSIUS_H
#define REFLOW_CELSIUS_H

#include <stdint.h>

// internal representation is the temp * 2^TEMP_POWER
// i.e. four times the temperature
#define TEMP_POWER 2
// define celsius and 0 and farenheit as 1
#define TEMP_UNITS_C  0
#define TEMP_UNITS_F  1

class Celsius {
public:
  // public constructor
  Celsius(void);
  // temperature setters
  // set to a temperature in celsius
  void set(int16_t c);
  // set to a temperature in celsius or farenheit
  void set(int16_t t, uint8_t units);
  // set the temperature with an int that is a power of 2 multiple of the temperature
  // c is the integer in celsius
  // power is the power of two by which the int is scaled
  // example - c=200, power=1 will set the temperature to 100
  void setScaled(int16_t c, uint8_t power);
  
  // temperature getter
  // returns the internal representation (i.e. 4*celsius)
  int16_t getScaled(void);

  // declare that boolean operators are friends
  friend bool operator==(const Celsius& lhs, const Celsius& rhs);
  friend bool operator!=(const Celsius& lhs, const Celsius& rhs);
  friend bool operator< (const Celsius& lhs, const Celsius& rhs);
  friend bool operator> (const Celsius& lhs, const Celsius& rhs);
  friend bool operator<=(const Celsius& lhs, const Celsius& rhs);
  friend bool operator>=(const Celsius& lhs, const Celsius& rhs);
  friend bool operator==(const Celsius& lhs, const int16_t& rhs);
  friend bool operator!=(const Celsius& lhs, const int16_t& rhs);
  friend bool operator< (const Celsius& lhs, const int16_t& rhs);
  friend bool operator> (const Celsius& lhs, const int16_t& rhs);
  friend bool operator<=(const Celsius& lhs, const int16_t& rhs);
  friend bool operator>=(const Celsius& lhs, const int16_t& rhs);
  
  // also addition and subtraction compound assignment with ints
  inline Celsius& operator+=(const int16_t& rhs) {
    this->setScaled(this->getScaled() + 4*rhs, 2);
    return *this;
  }
  inline Celsius& operator-=(const int16_t& rhs) {
    this->setScaled(this->getScaled() - 4*rhs, 2);
    return *this;
  }

private:
  // signed 16-bit int to hold the temperature
  // internal representation is 4x the temperature
  // this gives us 0.25 degree resolution in an int
  int16_t celsius;
};

// time to overload some opperators
// gonna need the comparison operators
inline bool operator==(const Celsius& lhs, const Celsius& rhs){return (lhs.celsius == rhs.celsius);}
inline bool operator!=(const Celsius& lhs, const Celsius& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Celsius& lhs, const Celsius& rhs){return (lhs.celsius < rhs.celsius);}
inline bool operator> (const Celsius& lhs, const Celsius& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Celsius& lhs, const Celsius& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Celsius& lhs, const Celsius& rhs){return !operator< (lhs,rhs);}
inline bool operator==(const Celsius& lhs, const int16_t& rhs){return (lhs.celsius == rhs<<TEMP_POWER);}
inline bool operator!=(const Celsius& lhs, const int16_t& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Celsius& lhs, const int16_t& rhs){return (lhs.celsius < rhs<<TEMP_POWER);}
inline bool operator> (const Celsius& lhs, const int16_t& rhs){return (lhs.celsius > rhs<<TEMP_POWER);}
inline bool operator<=(const Celsius& lhs, const int16_t& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Celsius& lhs, const int16_t& rhs){return !operator< (lhs,rhs);}


#endif