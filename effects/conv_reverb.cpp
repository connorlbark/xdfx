#include "include/ConvReverb.h"
#include "effects/entrypoints/reverb_fx_main.h"
#include CONV_REVERB_H


#include "userrevfx.h"
//static __sdram float imp_resp_ram[RAMLENGTH];
static __sdram float x_history_ram[IRSIZE];
static __sdram f32pair_t X_history_ram[IRSIZE];

static ConvReverb rev;

void MODFX_INIT(uint32_t platform, uint32_t api) {

}

void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn, float *sub_yn,
                   uint32_t frames) {
    distortion->tick(main_xn, main_yn, frames);
}

void MODFX_PARAM(uint8_t index, uint32_t value) {
    const float valf = q31_to_f32(value);

    if (index == k_user_modfx_param_time) {
        distortion->setTime(valf);
    }

    if (index == k_user_modfx_param_depth) {
        distortion->setDepth(valf);
    }
}