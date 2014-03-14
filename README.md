# reflow

Heater controller with thermocouple feedback to control any AC heating appliance. It was originally developed to turn a toaster oven into a solder reflow oven, but it'll control anything that runs on AC and gets hot.

## hardware v0.1

The current board contains an AVR ATMega328P microcontroller, a Sharp S212S01 solid-state relay, and an Analog Devices AD8495 K-type thermocouple amplifier. It has a temperature precision of about 0.5 degrees C and is accurate to about +/- 2 degrees C. It also has start, stop, and mode buttons; a rotary encoder for temperature settings; and a four-digit seven-segment display for showing temperature in C or F. 

The schematic and PCB layout files were created in [KiCad](http://www.kicad-pcb.org) and live the in `pcb` directory.

## firmware v0.1.1

The current firmware has two basic modes: hit and hold. Hit mode takes the temperature up to the set point and then shuts off, while hold mode attempts to hold the temperature at the set-point by turning the heat on when the temperature is below the set point, and off when it's above. This is not PID. It can also display the temperature in either Celsius or Fahrenheit.

The firmware is written in C++ and compiled on OS X using the latest [CrossPack for AVR](http://www.obdev.at/products/crosspack/index.html) and lives in the `firmware` directory. It'll probably compile fine on Linux; no idea about Windows, though.

## operation

* To switch temperature units, hold the set wheel down (it's also a button) until you see an F after the temperature (Fahrenheit) or a number with a decimal point (Celsius)
* To switch modes between hit and hold, press and release the set wheel button; the display will show either "hit" or "hold" for whatever mode has been selected
* To select a set point, turn the set wheel until the display shows your desired temperature
* Press the start button to start heating; the red light will go out and the green light will illuminate
	* In hit mode, once the temperature is hit, the heating will stop and the green light will go out, replaced by the red light
	* In hold mode, the program will not stop unless you tell it to
* Press the stop button to stop heating; the green light will go out and the red light will illuminate
* Whenever the relay is closed (i.e. heat is on) the red LED labeled "HOT" will illuminate

## things this board has been used for

* reflow toaster oven (in hit mode)
* sous vide slow-cooker (in hold mode)
