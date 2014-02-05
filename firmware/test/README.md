# reflow unit testing
Unit testing for classes in the reflow project using the [Google Test](https://code.google.com/p/googletest/) c++ testing framework.

Some classes for the reflow project do not interact with the hardware, so (in theory) we can check the math on the computer. That being said, **passing a test on the computer is not the same as passing a test on the real microprocessor**. Still, though, it's a nice sanity check.

To test:

1. `$ make`
2. `$ ./reflow_tests`
