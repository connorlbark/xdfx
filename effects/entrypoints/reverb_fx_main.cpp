//
// Created by Connor Barker on 8/27/21.
//

#include "reverb_fx_main.h"
#include "userrevfx.h"

Reverb *verb;

void REVFX_INIT(uint32_t platform, uint32_t api) {
    verb = generateReverb();
}

void REVFX_PROCESS(float *main_xn,
                   uint32_t frames) {
    verb->tick(main_xn, frames);
}

void REVFX_PARAM(uint8_t index, uint32_t value) {

    if (index == k_user_revfx_param_time) {
        verb->setTime(float(value)/1024.f);
    }

    if (index == k_user_revfx_param_depth) {
        verb->setDepth(float(value)/1024.f);
    }

    if (index == k_user_revfx_param_shift_depth) {
        verb->setDryWet(float(value)/1024.f);
    }
}