#include "include/ConvReverb.h"
#include "effects/entrypoints/reverb_fx_main.h"
#include CONV_REVERB_H


#include "userrevfx.h"
//static __sdram float imp_resp_ram[RAMLENGTH];
static __sdram float x_history_ram[IRSIZE];
static __sdram f32pair_t X_history_ram[IRSIZE];

Reverb  *generateReverb() {
    Buffer<f32pair_t> impulseResponse = Buffer<f32pair_t>(ir_data, IRSIZE);
    Buffer<float> x_history = Buffer<float>(x_history_ram, IRSIZE);
    Buffer<f32pair_t> X_history = Buffer<f32pair_t>(X_history_ram, IRSIZE);


    return nullptr;
}
