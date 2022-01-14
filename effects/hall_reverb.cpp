#include "include/HallReverb.h"
#include "effects/entrypoints/reverb_fx_main.h"


#include "userrevfx.h"

//static __sdram float imp_resp_ram[RAMLENGTH];
static __sdram float x_history[IRSIZE];
static __sdram float y_history[IRSIZE];

static HallReverb rev;

void MODFX_INIT(uint32_t platform, uint32_t api) {

}

void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn, float *sub_yn,
                   uint32_t frames) {
    rev->tick(main_xn, main_yn, frames);
}

void MODFX_PARAM(uint8_t index, uint32_t value) {
    const float valf = q31_to_f32(value);

    if (index == k_user_modfx_param_time) {
        rev->setTime(valf);
    }

    if (index == k_user_modfx_param_depth) {
        rev->setDepth(valf);
    }
}