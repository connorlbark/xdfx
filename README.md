# stdfx

WIP

This project aims to implement a variety of basic effects with the logue-sdk.

## Building

This project's makefile is similar to the original logue-sdk template makefile, but updated for our own needs.

All that needs to be changed to compile an effect is in `project.mk`.

First, set the path to minilogue-xd platform folder in the logue-sdk as `PLATFORMDIR`.

### FAQ

#### Why does MODFX_PROCESS() have *main* and *sub* inputs and outputs?

The modulation effect API was originally designed for the prologue synthesizer which allows each *main* and *sub* timbre
audio to be processed independently by the modulation effect section. This interface was maintained in order to preserve
API compatibility between the minilogue xd and prologue. For an effect to properly work on the prologue, both inputs
should be processed in the same way and the result written to the corresponding output.

## Setting Up

```c++
#include
"float_math.h"
#include
"include/Buffer.h"

typedef double real_type;
typedef buf_f32pair_t complex_type;

#ifndef
__USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR
#define
__USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR
#endif
```