//
// Created by Connor Barker on 9/1/21.
//

#ifndef STDFX_CONVREVERB_H
#define STDFX_CONVREVERB_H


#include "Buffer.h"
#include "Reverb.h"
#include "float_math.h"

class ConvReverb : public Reverb {
private:
    Buffer<buf_f32pair_t> impulseResponse;
    Buffer<float> history;
    Buffer<buf_f32pair_t> fft_buf;
public:
    ConvReverb(Buffer<buf_f32pair_t> impulseResponse, Buffer<float> history, Buffer<buf_f32pair_t> fft_buf);

    void tick(float *inout, uint32_t length) override;

};


#endif //STDFX_CONVREVERB_H
