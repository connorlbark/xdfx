//
// Created by Connor Barker on 1/12/22.
//

#ifndef STDFX_TAPDELAY_HPP
#define STDFX_TAPDELAY_HPP

#include "include/utils/Buffer.hpp"

class TapDelay {
private:
    Buffer<f32pair_t> buf;

    float wet_pct;
    float time_param;
    float depth_param;

    int16_t sample_delay() const {
        return int(this->time_param * float(this->buf.length()));
    };

    float feedback() const {
        return this->depth_param;
    };


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

    TapDelay(f32pair_t * ram, int length) : buf(ram, length) {
    }


    void tick(float *inout, uint32_t length)  {

        for (int i = 0; i < length; i++) {
            float l = inout[2*i];
            float r = inout[2*i+1];

            this->buf.prepend(f32pair(l*feedback(),r*feedback()));
            f32pair_t delayed = this->buf[this->sample_delay()];

            inout[2*i] = l * (1.f-this->wet_pct) + delayed.a * this->wet_pct;
            inout[2*i+1] = r * (1.f-this->wet_pct) + delayed.b * this->wet_pct;
        }
    }

};


#endif //STDFX_TAPDELAY_HPP
