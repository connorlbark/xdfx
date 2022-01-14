//
// Created by Connor Barker on 10/5/21.
//

#include "../include/SigmoidDistortion.h"
#include "usermodfx.h"

#define HISTLENGTH 30
static __sdram float history[HISTLENGTH];
static SigmoidDistortion distortion{history, HISTLENGTH};

void MODFX_INIT(uint32_t platform, uint32_t api) {


}

void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn, float *sub_yn,
                   uint32_t frames) {
    distortion.tick(main_xn, main_yn, frames);
}

void MODFX_PARAM(uint8_t index, int32_t value) {
    const float valf = q31_to_f32(value);
    switch (index) {
        case k_user_modfx_param_time:
            distortion.setTime(valf);
            break;
        case k_user_modfx_param_depth:
            distortion.setDepth(valf);
            break;
        default:
            break;
    }
}