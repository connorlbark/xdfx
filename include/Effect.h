//
// Created by Connor Barker on 9/1/21.
//

#ifndef STDFX_EFFECT_H
#define STDFX_EFFECT_H

#include <cstdint>

class Effect {
public:
    virtual void tick(const float *in, float *out, uint32_t length) = 0;

    virtual void setTime(uint32_t val) = 0;

    virtual void setDepth(uint32_t val) = 0;
};


#endif //STDFX_EFFECT_H
