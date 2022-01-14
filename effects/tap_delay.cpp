#include "include/TapDelay.h"


#include "userdelfx.h"

const int ram_size = 48000/2;
//static __sdram float imp_resp_ram[RAMLENGTH];
static __sdram float l_history[ram_size];
static __sdram float r_history[ram_size];

static TapDelay del{l_history, r_history, ram_size};

void DELFX_INIT(uint32_t platform, uint32_t api) {

}

void DELFX_PROCESS(float *inout,
                   uint32_t frames) {
    del.tick(inout, frames);
}

void DELFX_PARAM(uint8_t index, uint32_t value) {
    const float valf = q31_to_f32(value);

    if (index == k_user_delfx_param_time) {
        del.setTime(valf);
    }

    if (index == k_user_delfx_param_depth) {
        del.setDepth(valf);
    }

    if (index == k_user_delfx_param_shift_depth) {
        del.setDryWet(valf);
    }
}