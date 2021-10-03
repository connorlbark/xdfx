//
// Created by Connor Barker on 8/27/21.
//

#ifndef STDFX_COMBFILTER_H
#define STDFX_COMBFILTER_H

#include <vector>
#include "../Filter.h"

class CombFilter : public Filter {
private:
    std::vector<float> FF;
    std::vector<float> FB;

    std::vector<float> inputState;
    std::vector<float> outputState;

    static std::vector<float> genState(const float *raw, uint32_t rawLength, uint32_t stateLength);

    void updateStates(const float *in, const float *out, uint32_t length);

    static float sample(std::vector<float> state, const float *raw, int idx);

public:
    CombFilter(std::vector<float> FF, std::vector<float> FB);

    void setResonance(uint32_t val) override;

    void setCutoff(uint32_t val) override;

    void tick(const float *in, float *out, uint32_t length) override;
};


#endif //STDFX_COMBFILTER_H
