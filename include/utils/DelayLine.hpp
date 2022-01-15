//
// Created by Connor Barker on 1/14/22.
//

#ifndef STDFX_DELAYLINE_HPP
#define STDFX_DELAYLINE_HPP


#include "Buffer.hpp"
#include "Control.hpp"

class DelayLine  {
private:
    Buffer buf;
    Control delay;

public:
    DelayLine(buf_f32pair_t *ram, int ram_length, Control delay) : buf(ram, ram_length),
                                                                                    delay(delay) {
    }


    buf_f32pair_t tick(buf_f32pair_t sample) {
        int16_t sampleDelay = this->delay.get();

        // if there is no delay, then just return the sample; otherwise look into the buffer
        buf_f32pair_t delayedSample = (sampleDelay == 0 ? sample : this->buf[sampleDelay-1]);

        // add sample to buffer
        this->buf.prepend(sample);

        return delayedSample;
    }

    void setDelay(Control delay) {
        this->delay = delay;
    }

    int maxDelay() const {
        return this->buf.length();
    }

};

#endif //STDFX_DELAYLINE_HPP
