//
// Created by Connor Barker on 1/14/22.
//

#ifndef STDFX_DELAYLINE_HPP
#define STDFX_DELAYLINE_HPP

#endif //STDFX_DELAYLINE_HPP

#include "Node.hpp"
#include "Buffer.h"
#include "include/utils/control/Control.hpp"

class DelayLine : public Node {
private:
    Buffer<buf_f32pair_t> buf;
    Control delay;

public:

    DelayLine(buf_f32pair_t *ram, int ram_length, Control delay) : buf(ram, ram_length),
                                                                                  delay(std::move(delay)) {
    }

    buf_f32pair_t tick(buf_f32pair_t sample) {
        int16_t sampleDelay = this->delay.get();

        buf_f32pair_t delayedSample = this->buf[sampleDelay];
        this->buf.prepend(sample);

        return delayedSample;
    }

};