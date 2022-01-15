//
// Created by Connor Barker on 1/12/22.
//

#ifndef STDFX_TAPDELAY_HPP
#define STDFX_TAPDELAY_HPP

#include "include/utils/Buffer.hpp"
#include "include/utils/DelayLine.hpp"

class TapDelay {
private:
    DelayLine delayLine;

    float wet_pct = 0.0f;
    float time_param = 0.0f;
    float depth_param = 0.0f;

    int16_t sample_delay() const {
        return int(this->time_param * float(this->delayLine.maxDelay()));
    };

    float feedback() const {
        return this->depth_param;
    };


public:


    void setTime(float val) {
        this->time_param = val;
        this->delayLine.setDelay(this->sample_delay());
    };

    void setDepth(float val) {
        this->depth_param = val;
    }

    void setDryWet(float val) {
        this->wet_pct = val;
    }

    TapDelay(buf_f32pair_t * ram, int length) : delayLine(ram, length, 0) {
    }


    void tick(float *inout, uint32_t length)  {

        for (int i = 0; i < length; i++) {
            float l = inout[2*i];
            float r = inout[2*i+1];

            buf_f32pair_t delayed = this->delayLine.tick(buf_f32pair_t(l,r) * feedback());

            inout[2*i] = l * (1.f-this->wet_pct) + delayed.a * this->wet_pct;
            inout[2*i+1] = r * (1.f-this->wet_pct) + delayed.b * this->wet_pct;
        }
    }

};


#endif //STDFX_TAPDELAY_HPP
