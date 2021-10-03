//
// Created by Connor Barker on 9/8/21.
//

#ifndef STDFX_DELAY_H
#define STDFX_DELAY_H


class Delay {
public:
    virtual void tick(const float *in, float *out, uint32_t length) = 0;

    virtual void setTime(uint32_t val) = 0;

    virtual void setDepth(uint32_t val) = 0;

    virtual void setDryWet(uint32_t val) = 0;
};


#endif //STDFX_DELAY_H
