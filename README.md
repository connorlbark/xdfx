# xdfx

WIP

I'm currently trying to learn a lot of basic DSP algorithms, 
and this project is me playing around with effects for my minilogue-xd synth :)

Currently, effects include:
- Tape Distortion
- Hall reverb (WIP)
- Tap delay (WIP)

## Building

This project's makefile is similar to the original logue-sdk template makefile, but changed to allow compiling different
effects within the same project.

All that needs to be changed is in `project.mk`.

First, set the path to minilogue-xd platform folder in the logue-sdk as `PLATFORMDIR`.

Next, set which effect you want to compile at `EFFECT`. Check if there are any
settings you want to change in the effect's parameters.

Finally, run `make all`.
