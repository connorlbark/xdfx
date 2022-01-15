//
// Created by Connor Barker on 1/14/22.
//

#ifndef STDFX_CONTROL_HPP
#define STDFX_CONTROL_HPP

#include "float_math.h"

enum ModulationType {
    none,
    sine,
    sawtooth
};

class Modulation {
private:
    ModulationType type;

    float amplitude;
    float phase;
    uint16_t sampleCounter;
    uint16_t samplesPerCycle; // sr=48000hz
    uint8_t bitdepth;

    // [0.0, 1.0] -> [-1.0, 1.0]
    float waveform(float in) {
        switch (this->type) {
            case ModulationType::sine:
                return fastsinf((in - 0.5f) * M_PI * 2.f);
            case ModulationType::sawtooth:
                return (in - 0.5f) * 2.f;
            default:
                return 0.f;
        }
    }

public:

    Modulation() : type(ModulationType::none), amplitude(0.f), phase(0.f), sampleCounter(0), samplesPerCycle(0),
                   bitdepth(0) {};

    Modulation(ModulationType type, float amplitude, float phase, uint16_t samplesPerCycle, uint16_t bitdepth) : type(
            type), amplitude(amplitude), phase(phase), sampleCounter(0), samplesPerCycle(samplesPerCycle), bitdepth(
            bitdepth) {

    }

    int16_t get() {
        if (this->type == ModulationType::none) { return 0; }

        float valf = amplitude * this->waveform(float(this->sampleCounter) / float(this->samplesPerCycle) + this->phase);

        this->sampleCounter++;
        if (this->sampleCounter >= samplesPerCycle) {
            this->sampleCounter = 0; // has done a full revolution; reset ticks
        }

        if (this->bitdepth < 16) {
            float numBins = powf(2.f, this->bitdepth);

            float remainder = fmodf(valf, amplitude / float(numBins));

            // Quantize ...
            valf = valf - remainder;
        }

        return int(valf);
    }

};

class Control {
private:
    int16_t mean;
    Modulation modulation;

public:
    Control(int16_t val) : mean(val), modulation() {};
    Control(int16_t val, Modulation modulation) : mean(val), modulation(modulation) {};

    int16_t get() { return mean + this->modulation.get(); };
};

#endif //STDFX_CONTROL_HPP

