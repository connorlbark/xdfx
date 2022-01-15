# #############################################################################
# Project Customization
# #############################################################################


PLATFORMDIR = ../logue-sdk/platform/minilogue-xd

THIRDPARTYLIBS = third_party/Simple-FFT/include

EFFECT = 4
# 1 = Hall Reverb
# 2 = Chebyshev Distortion
# 3 = Tape Distortion
# 4 = Tap Delay

# EFFECT PARAMETERS ARE BELOW

# Hall Reverb
ifeq ($(EFFECT),1)
	PROJECT = hall_reverb

	UCSRC = # c source files

	UCXXSRC = effects/hall_reverb.cpp # c++11 source files

	MANIFEST = effects/manifests/hall_reverb.json
endif

# Chebyshev Distortion
ifeq ($(EFFECT),2)
	PROJECT = basic_distortion

	UCSRC = # c source files

	UCXXSRC = effects/basic_distortion.cpp # c++11 source files

	MANIFEST = effects/basic_distortion/manifest.json
endif

# Tape Distortion
ifeq ($(EFFECT),3)
	PROJECT = tape_distortion

	UCSRC = # c source files

	UCXXSRC = effects/tape_distortion.cpp # c++11 source files

	MANIFEST = effects/tape_distortion/manifest.json
endif

# Tap Delay
ifeq ($(EFFECT),4)
	PROJECT = tap_delay

	UCSRC = # c source files

	UCXXSRC = effects/tap_delay.cpp # c++11 source files

	MANIFEST = effects/tap_delay/manifest.json
endif

UINCDIR = # header search paths

UDEFS = # custom gcc flags

ULIB = # linker flags

ULIBDIR = # linker search paths

