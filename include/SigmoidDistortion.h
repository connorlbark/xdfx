//
// Created by Connor Barker on 11/3/21.
//

#ifndef STDFX_SIGMOIDDISTORTION_H
#define STDFX_SIGMOIDDISTORTION_H

#include "ModEffect.h"
#include "float_math.h"

class SigmoidDistortion : public ModEffect {
private:
    float *history;
    int history_length;


    float sigmoid(float inp) {
        return 1.f / (1.f + fastexpf(-1.f * inp));
    }

    float integrate(float inp) {
        float scalar = 1.f / float(history_length + 1);
        float sum = inp * scalar;

        for (int i = 0; i < history_length; i++) {
            sum += this->history[i] * scalar;
        }

        return sum;
    }

protected:


    float apply(float sample) {
        return this->sigmoid(this->integrate(sample));
    }

public:
    SigmoidDistortion(float *history, int history_length) : history(history),
                                                            history_length(history_length) {

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
