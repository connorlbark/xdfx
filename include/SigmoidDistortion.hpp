//
// Created by Connor Barker on 11/3/21.
//

#ifndef STDFX_SIGMOIDDISTORTION_H
#define STDFX_SIGMOIDDISTORTION_H

#include "ModEffect.h"
#include "float_math.h"
#include "utils/Buffer.hpp"

class SigmoidDistortion : public ModEffect {
private:
    Buffer<float> history;


    static float sigmoid(float inp) {
        return 1.f / (1.f + fastexpf(-1.f * inp));
    }

    float integrate() {
        int length = int(float(this->history.length()) * this->depth);
        if (length < 3) {
            length = 3;
        }

        float sum = 0.0;

        for (int i = 0; i < length; i++) {
            sum += this->history[i] * float(length - i -1) / float(length);
        }

        return sum / float(length);
    }

protected:


    float apply(float sample) {
        this->history.append(sample);
        return SigmoidDistortion::sigmoid(SigmoidDistortion::sigmoid(this->integrate() * (1.f+ this->time)));
    }

public:
    SigmoidDistortion(float *history, int history_length) : history(history, history_length) {
    }

    void tick(const float *in, float *out, uint32_t inp_length) override {
        const float *mx = in;
        float *__restrict my = out;
        const float *my_e = my + 2 * inp_length;

        for (; my != my_e;) {
            *(my++) = clip1m1f(this->apply(*(mx++)));
        }
    }


};

#endif //STDFX_SIGMOIDDISTORTION_H
