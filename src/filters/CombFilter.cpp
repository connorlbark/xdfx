//
// Created by Connor Barker on 8/27/21.
//

#include "../../include/filters/CombFilter.h"

#include <utility>

CombFilter::CombFilter(std::vector<float> FF, std::vector<float> FB) : FF(std::move(FF)), FB(std::move(FB)) {}


void CombFilter::setResonance(uint32_t val) {
    // do nothing, since resonance has no concept in a
    // comb filter
}

void CombFilter::setCutoff(uint32_t val) {
    // do nothing, since cutoff has no concept in a
    // comb filter
}

void CombFilter::tick(const float *in, float *out, uint32_t length) {
    for (int sampleIdx = 0; sampleIdx < length; sampleIdx++) {
        float sampleVal = 0.0;

        for (int ffIdx = 0; ffIdx < this->FF.size(); ffIdx++) {
            int ffSampleIdx = sampleIdx - ffIdx;

            float ffSample = CombFilter::sample(this->inputState, in, ffSampleIdx);

            // add feedforward with the gain applied
            sampleVal += ffSample * this->FF[ffIdx];
        }

        for (int fbIdx = 0; fbIdx < this->FF.size(); fbIdx++) {
            int fbSampleIdx = sampleIdx - fbIdx;

            float fbSample = CombFilter::sample(this->outputState, out, fbSampleIdx);

            // add feedback with the gain applied
            sampleVal -= fbSample * this->FB[fbIdx];
        }

        *(out + sampleIdx) = sampleVal;
    }


}

float CombFilter::sample(std::vector<float> state, const float *raw, int idx) {
    float sample = 0.0;

    // is the desired feedback value
    // a part of the saved state (e.g.
    // it goes before the 0th element)?
    if (idx < 0) {
        if (!state.empty()) {
            // end of saved state is the sample before
            // the beginning of *out; note that idx
            // is always negative
            sample = state.at(state.size() + idx);
        } else {
            // sample default value is empty, or 0.0
            sample = 0.0;
        }
    } else {
        sample = *(raw + idx);
    }

    return sample;
}

std::vector<float> CombFilter::genState(const float *raw, uint32_t rawLength, uint32_t stateLength) {
    std::vector<float> state = std::vector<float>(stateLength);

    for (int i = stateLength - 1; i >= 0; i++) {
        // extract
        // n-stateLength,n-stateLength+1,...,n
        // in strictly that order
        state.push_back(
                *(raw + (rawLength - 1) - stateLength)
        );
    }

    return state;
}

void CombFilter::updateStates(const float *in, const float *out, uint32_t length) {
    this->inputState = genState(in, length, this->FF.size());
    this->outputState = genState(out, length, this->FB.size());
}


