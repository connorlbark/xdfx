//
// Created by Connor Barker on 1/11/22.
//

#ifndef STDFX_ALGORITHMICREVERB_H
#define STDFX_ALGORITHMICREVERB_H

#include "utils/Buffer.h"

class HallReverb {
private:
    Buffer<float> x_history;
    Buffer<float> y_history;

    float comb_filter(float sample, float g, int d) {
        return sample + g * this->y_history[d-1];
    }

    float all_pass_filter(float sample, float g, int d) {
        return -g * sample + this->x_history[d-1] + g * this->y_history[d-1];
    }
public:
    HallReverb(float *x_history_ram, float *y_history_ram, int ram_size) : x_history(x_history_ram, ram_size),
                                                                           y_history(y_history_ram, ram_size) {

        this->x_history.fill(0.0);
        this->y_history.fill(0.0);
    };


};


#endif //STDFX_ALGORITHMICREVERB_H
