//
// Created by Connor Barker on 1/12/22.
//

#ifndef STDFX_TAPDELAY_H
#define STDFX_TAPDELAY_H

#include "include/utils/Buffer.h"
#include "Reverb.h"
#include "include/utils/AllPassLoop.hpp"
#include "include/utils/control/SineModulation.hpp"

class TapDelay : public Reverb {
private:
    Buffer<float> y_l_history;
    Buffer<float> y_r_history;

    int sample_delay() const {
        return int(this->time_param * this->y_l_history.length());
    };

    float feedback() const {
        return this->depth_param;
    };

public:

    TapDelay(float * l_history, float * r_history, int length) : y_l_history(l_history, length), y_r_history(r_history, length) {
        this->y_l_history.fill(0.0);
        this->y_r_history.fill(0.0);
    }

    void tick(float *inout, uint32_t length) {

        for (int i = 0; i < length; i++) {
            float l = inout[2*i];
            float r = inout[2*i+1];

            this->y_l_history.prepend(l * this->feedback());
            this->y_r_history.prepend(r * this->feedback());

            inout[2*i] = l * (1-this->wet_pct) + this->y_l_history[this->sample_delay() - 1] * this->wet_pct;
            inout[2*i+1] = r * (1-this->wet_pct) + this->y_r_history[this->sample_delay() - 1] * this->wet_pct;
        }
    }

};


#endif //STDFX_TAPDELAY_H
