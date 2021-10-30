//
// Created by Connor Barker on 9/1/21.
//

#ifndef STDFX_EFFECT_H
#define STDFX_EFFECT_H

#include <cstdint>

class ModEffect {
protected:
    float time = 0.0f;
    float depth = 0.0f;
public:
    virtual void tick(const float *in, float *out, uint32_t length) = 0;

    virtual void setTime(float val) {
        this->time = val;
    }

    virtual void setDepth(float val) {
        this->depth = val;
    }
};


#endif //STDFX_EFFECT_H
