# #############################################################################
# Project Customization
# #############################################################################


PLATFORMDIR = ../logue-sdk/platform/minilogue-xd

THIRDPARTYLIBS = third_party/Simple-FFT/include

EFFECT = 1
# 0 = Comb Filter
# 1 = Convolution Reverb (set CONV_REVERB_PATH to the impulse response you'd like to embed)

ifeq ($(EFFECT),0)
	PROJECT = comb

	UCSRC = # c source files

	UCXXSRC = comb.cpp src/filters/CombFilter.cpp src/Filter.cpp effect_fx_main.cpp src/mathops.cpp # c++11 source files

	MANIFEST = manifests/comb.json
endif

ifeq ($(EFFECT),1)
	PROJECT = conv_reverb

	UCSRC = # c source files

	UCXXSRC = conv_reverb.cpp src/ConvReverb.cpp src/Reverb.cpp reverb_fx_main.cpp # c++11 source files

	MANIFEST = manifests/conv_reverb.json

	CONV_REVERB_PATH = rev_ir/example.h
endif

UINCDIR = # header search paths

UDEFS = # custom gcc flags

ULIB = # linker flags

ULIBDIR = # linker search paths

