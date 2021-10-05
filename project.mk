# #############################################################################
# Project Customization
# #############################################################################


PLATFORMDIR = ../logue-sdk/platform/minilogue-xd

THIRDPARTYLIBS = third_party/Simple-FFT/include

EFFECT = 1
# 0 = Comb Filter
# 1 = Convolution Reverb (set CONV_REVERB_PATH to the impulse response you'd like to embed)
# 2 = Distortion

# EFFECT PARAMETERS ARE BELOW

# Comb Filter
ifeq ($(EFFECT),0)
	PROJECT = comb

	UCSRC = # c source files

	UCXXSRC = effects/comb.cpp src/filters/CombFilter.cpp src/Filter.cpp effects/entrypoints/effect_fx_main.cpp src/mathops.cpp # c++11 source files

	MANIFEST = effects/manifests/comb.json
endif

# Convolution Reverb
ifeq ($(EFFECT),1)
	PROJECT = conv_reverb

	UCSRC = # c source files

	UCXXSRC = effects/conv_reverb.cpp src/ConvReverb.cpp src/Reverb.cpp effects/entrypoints/reverb_fx_main.cpp # c++11 source files

	MANIFEST = effects/manifests/conv_reverb.json

	CONV_REVERB_PATH = effects/rev_ir/example.h # change this to whatever reverb IR you want.
endif

# Distortion
ifeq ($(EFFECT),2)
	PROJECT = basic_distortion

	UCSRC = # c source files

	UCXXSRC = effects/basic_distortion.cpp src/ChebyshevDistortion.cpp src/Effect.cpp effects/entrypoints/mod_fx_main.cpp # c++11 source files

	MANIFEST = manifests/basic_distortion.json
endif

UINCDIR = # header search paths

UDEFS = # custom gcc flags

ULIB = # linker flags

ULIBDIR = # linker search paths

