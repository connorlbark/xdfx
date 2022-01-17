//
// Created by Connor Barker on 1/12/22.
//

#ifndef STDFX_VIBRATO_HPP
#define STDFX_VIBRATO_HPP

#include "include/utils/Buffer.hpp"

class Vibrato {
private:
    Buffer<f32pair_t> buf;

    float time_param;
    float depth_param;

    int16_t sampleTickCounter;

    int16_t mod_amplitude() const {
        return int(this->time_param * float(this->buf.length()));
    };

    uint16_t mod_rate() const {
        return int((1.f-this->depth_param) * 1024.f) // todo: constant
    };

    float mod_source(float in) {
        return fastsinf((in - 0.5f) * M_PI * 2.f);
    }

    int16_t tick_delay_mod() {
        uint16_t mod_rate = this->mod_rate();

        int16_t mod = int16_t(float(this->mod_amplitude()) * this->waveform(float(this->sampleTickCounter) / float(mod_rate)));
        this->sampleTickCounter++;
        if (this->sampleTickCounter >= mod_rate) {
            this->sampleTickCounter %= mod_rate;
        }

        return mod;
    }

public:


    void setTime(float val) {
        this->time_param = val;
    };

    void setDepth(float val) {
        this->depth_param = val;
    }

    void setDryWet(float val) {
        this->wet_pct = val;
    }

    Vibrato(f32pair_t * ram, int length) : buf(ram, length) {
    }


    void tick(float *inout, uint32_t length)  {

        for (int i = 0; i < length; i++) {
            float l = inout[2*i];
            float r = inout[2*i+1];

            this->buf.prepend(f32pair(l,r));
            f32pair_t delayed = this->buf[this->delay_mod()];

            inout[2*i] = delayed;
            inout[2*i+1] = delayed;
        }
    }

};


#endif //STDFX_VIBRATO_HPP
