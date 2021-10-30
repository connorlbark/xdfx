//
// Created by Connor Barker on 10/5/21.
//

#include "entrypoints/mod_fx_main.h"
#include "../include/ChebyshevDistortion.h"
#include "usermodfx.h"

#define COEFFLENGTH 10
static __sdram float coefficients[COEFFLENGTH];
static ChebyshevDistortion distortion{coefficients, COEFFLENGTH};

void MODFX_INIT(uint32_t platform, uint32_t api) {

    coefficients[0] = 1.f;
    coefficients[1] = 0.33f;
    coefficients[2] = 0.2f;
    coefficients[3] = 0.1f;
    coefficients[4] = 0.1f;
    coefficients[5] = 0.05f;
    coefficients[6] = 0.05f;
    coefficients[7] = 0.000f;
    coefficients[8] = 0.000f;
    coefficients[9] = 0.000f;

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