//
// Created by Connor Barker on 1/14/22.
//

#ifndef STDFX_SINEMODULATION_HPP
#define STDFX_SINEMODULATION_HPP

#endif //STDFX_SINEMODULATION_HPP

#include "Control.hpp"
#include "float_math.h"

class SineModulation : public Control {
private:
    Control src;

    float amplitude;
    uint16_t ticksPerCycle;
    float phase;
    uint8_t modbitdepth;
    uint16_t ticks;
public:

    SineModulation(Control src, float amplitude, uint16_t ticksPerCycle, float phase, uint8_t modbitdepth) : src(src),
                                                                                                             amplitude(
                                                                                                                     amplitude),
                                                                                                             ticksPerCycle(
                                                                                                                     ticksPerCycle),
                                                                                                             phase(phase),
                                                                                                             modbitdepth(
                                                                                                                     modbitdepth),
                                                                                                             ticks(0) {};

    SineModulation(Control src, float amplitude, uint16_t ticksPerCycle, float phase) : SineModulation(src, amplitude,
                                                                                                       ticksPerCycle,
                                                                                                       phase, 32) {};

    SineModulation(Control src, float amplitude, uint16_t ticksPerCycle) : SineModulation(src, amplitude, ticksPerCycle,
                                                                                          0.0, 32) {};


    int16_t get() {
        return this->src.get() + this->modulation();

    }

    int16_t modulation() {
        float valf = amplitude * fastsinf(float(this->ticks) / float(this->ticksPerCycle) + this->phase);

        this->ticks++;
        if (this->ticks >= ticksPerCycle) {
            this->ticks = 0; // has done a full revolution; reset ticks
        }

        if (this->modbitdepth < 16) {
            float numBins = powf(2.f, this->modbitdepth);

            float remainder = fmodf(valf, 1.f / float(numBins));

            // Quantize ...
            valf = valf - remainder;
        }

        return int(valf);
    }
};