//
// Created by Connor Barker on 9/8/21.
//

#ifndef STDFX_REVERB_H
#define STDFX_REVERB_H

#include <cstdint>

class Reverb {
protected:
    float wet_pct = 0.0f;
    float time_param = 0.0f;
    float depth_param = 0.0f;

public:

    virtual void tick(float *inout, uint32_t length) = 0;

    void setTime(float val) {
        this->time_param = val;
    };

    virtual void setDepth(float val) {
        this->depth_param = val;
    }

    virtual void setDryWet(float val) {
        this->wet_pct = val;
    }
};

#endif //STDFX_REVERB_H
