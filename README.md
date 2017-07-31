# silly

A toy library implementing fixed-point arithmetic.
Please don’t use it, the name is descriptive.

It’s also pretty inefficient.

## Installation

Don’t. The makefile only includes a test target, because I want to test my code.

## Usage

```c
silly silly_zeros(); // creates a fixed point value of zero
silly make_silly(short, int, int); // make a silly number from the triple (negative?, before decimal, after)
silly silly_from_float(float); // creates a silly number from a float
silly silly_from_double(double); // creates a silly number from a double

double silly_to_double(silly); // convert a silly number into a double

silly silly_add(silly, silly); // addition
silly silly_sub(silly, silly); // subtraction
silly silly_mul(silly, silly); // multiplication

char* silly_to_string(silly); // converts a fixed point value to a string (memory is now yours)
```

That's it!

<hr/>

Have fun!
