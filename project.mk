# #############################################################################
# Project Customization
# #############################################################################


PLATFORMDIR = ../logue-sdk/platform/minilogue-xd

THIRDPARTYLIBS = third_party/Simple-FFT/include

EFFECT = 5
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

	UCXXSRC = effects/basic_distortion.cpp src/ChebyshevDistortion.cpp src/Effect.cpp # c++11 source files

	MANIFEST = effects/basic_distortion/manifest.json
endif

# Distortion
ifeq ($(EFFECT),3)
	PROJECT = tape_distortion

	UCSRC = # c source files

	UCXXSRC = effects/tape_distortion.cpp src/SigmoidDistortion.cpp src/Effect.cpp # c++11 source files

	MANIFEST = effects/tape_distortion/manifest.json
endif

# Distortion
ifeq ($(EFFECT),4)
	PROJECT = hall_reverb

	UCSRC = # c source files

	UCXXSRC = effects/HallReverb.cpp src/HallReverb.cpp src/Effect.cpp # c++11 source files

	MANIFEST = effects/hall_reverb/manifest.json
endif

ifeq ($(EFFECT),5)
	PROJECT = tap_delay

	UCSRC = # c source files

	UCXXSRC = src/TapDelay.cpp effects/tap_delay.cpp # c++11 source files

	MANIFEST = effects/tap_delay/manifest.json
endif

UINCDIR = # header search paths

UDEFS = # custom gcc flags

ULIB = # linker flags

ULIBDIR = # linker search paths

