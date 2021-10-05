# stdfx

WIP

This project aims to implement a variety of basic effects with the logue-sdk.

## Building

This project's makefile is similar to the original logue-sdk template makefile, but updated for our own needs.

All that needs to be changed to compile an effect is in `project.mk`.

First, set the path to minilogue-xd platform folder in the logue-sdk as `PLATFORMDIR`.

Next, set which effect you want to compile at `EFFECT`. Check if there are any
settings you want to change in the effect's parameters.

Finally, run `make all`.

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