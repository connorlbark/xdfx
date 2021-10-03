//
// Created by Connor Barker on 8/27/21.
//

#include "mod_fx_main.h"

std::unique_ptr<Effect> currEffect;

void MODFX_INIT(uint32_t platform, uint32_t api) {
    currEffect = generateEffect();
}

void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn, float *sub_yn,
                   uint32_t frames) {
    currEffect->tick(main_xn, main_yn, frames);
}

void MODFX_PARAM(uint8_t index, uint32_t value) {

    if (index == k_user_modfx_param_time) {
        currEffect->setTime(value);
    }

    if (index == k_user_modfx_param_depth) {
        currEffect->setDepth(value);
    }
}