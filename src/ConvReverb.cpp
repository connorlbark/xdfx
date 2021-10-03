//
// Created by Connor Barker on 9/1/21.
//

#include "../include/ConvReverb.h"
#include "simple_fft/fft.h"
#include "float_math.h"

ConvReverb::ConvReverb(Buffer<buf_f32pair_t> impulseResponse, Buffer<float> history, Buffer<buf_f32pair_t> fft_buf)
        : impulseResponse(impulseResponse), history(history), fft_buf(fft_buf) {}

void ConvReverb::tick(float *inout, uint32_t length) {

    for (int i = 0; i < length; i++) {
        this->history.prepend(*(inout + i));
    }

    const char *error = nullptr;
    simple_fft::FFT(history, fft_buf, length, error);
    if (error != nullptr) {
        // TODO
        return;
    }

    // TODO: just to ensure the sound is intact.
    //fft_buf.mult_inplace(this->impulseResponse);

    simple_fft::IFFT(fft_buf, this->fft_buf.length(), error);
    if (error != nullptr) {
        // TODO
        return;
    }

    Buffer<float> output = Buffer<float>(inout, length, length);

    float dry_pct = 1.f - this->wet_pct;

    for (int i = 0; i < output.length(); i++) {
        output[i] = dry_pct * output[i] + wet_pct * (fft_buf[i].a);
    }


}
