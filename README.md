# silly

A toy library implementing fixed-point arithmetic.
Please don't use it, the name is descriptive.

## Installation

Don't. The makefile only includes a test target, because I want to test my code.

## Usage

```c
silly silly_zeros(); // creates a fixed point value of zero

silly silly_add(silly, silly); // addition
silly silly_sub(silly, silly); // subtracttion

char* silly_to_string(silly); // converts a fixed point value to a string (memory is now yours)
```

That's it!

<hr/>

Have fun!