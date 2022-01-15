//
// Created by Connor Barker on 1/14/22.
//

#ifndef STDFX_ALLPASSLOOP_HPP
#define STDFX_ALLPASSLOOP_HPP

#endif //STDFX_ALLPASSLOOP_HPP

#include "Buffer.hpp"
#include "include/utils/control/Control.hpp"

class AllPassLoop  {
private:
    Buffer<buf_f32pair_t> buf;
    Control delay;
    float coeff;

public:

    AllPassLoop(buf_f32pair_t *ram, int ram_length, float coeff, Control delay) : buf(ram, ram_length),
                                                                                  delay(std::move(delay)),
                                                                                  coeff(coeff) {
    }

    buf_f32pair_t tick(buf_f32pair_t sample) {
        int16_t sampleDelay = this->delay.get();

        buf_f32pair_t delayedSample = this->buf[sampleDelay];
        this->buf.prepend(sample);

        return sample * -this->coeff + delayedSample * this->coeff;
    }

};