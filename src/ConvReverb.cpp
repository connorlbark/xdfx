//
// Created by Connor Barker on 9/1/21.
//

#include "../include/ConvReverb.h"
#include "simple_fft/fft.h"
#include "float_math.h"

ConvReverb::ConvReverb()
        : impulseResponse(nullptr, 0), history(nullptr, 0), fft_buf(nullptr, 0) {};

void ConvReverb::set_memory(buf_f32pair_t *impulseResponse, float *history, buf_f32pair_t *fft_buf, int length) {
    this->impulseResponse = Buffer<buf_f32pair_t>(impulseResponse, length);
    this->history = Buffer<float>(history, length);
    this->fft_buf = Buffer<buf_f32pair_t>(fft_buf, length);
}

void ConvReverb::tick(float *inout, uint32_t length) {
    int i = 1;

    // in the case that the incoming chunk of audio is longer than the impulse response, we need to apply the convolution
    // multiple times. For example, if the incoming audio chunk is 64 samples, and the impulse response is 32, then
    // we must apply it from 0->32, then 33->64.
    while (i < length) {
        if ((i % this->impulseResponse.length()) == 0) {
            this->apply_reverb((inout + i - this->impulseResponse.length()), this->impulseResponse.length());
        }

        i++;
    }

    // if the length of the impulse response does not go evenly into the incoming chunk of audio, for example if the
    // audio is 64 samples and the IR is 40, then there will be 24 samples left over. To handle this, we recompute the
    // values from 24->64 to fill in those last values.
    int samples_left = (i % this->impulseResponse.length());
    if (samples_left != 0) {
        this->apply_reverb((inout+length-1-samples_left), samples_left);
    }
}

void ConvReverb::apply_reverb(float *out, uint32_t length) {
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

    Buffer<float> output = Buffer<float>(out, length, length);

    float dry_pct = 1.f - this->wet_pct;

    for (int i = 0; i < length; i++) {
        int out_idx = length - 1 - i;
        int fft_idx = fft_buf.length() - 1 - i;

        output[out_idx] = dry_pct * output[out_idx] + wet_pct * (fft_buf[fft_idx].a);
    }
}
