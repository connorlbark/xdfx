//
// Created by Connor Barker on 8/27/21.
//

#ifndef STDFX_FILTER_H
#define STDFX_FILTER_H

#include <cstdint>
#include "ModEffect.h"

class Filter : public Effect {
public:
    virtual void tick(const float *in, float *out, uint32_t length) = 0;

    virtual void setCutoff(uint32_t val) {
        this->setTime(val);
    };

    virtual void setResonance(uint32_t val) {
        this->setDepth(val);
    };
};


#endif //STDFX_FILTER_H
