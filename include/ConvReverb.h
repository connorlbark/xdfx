//
// Created by Connor Barker on 9/1/21.
//

#ifndef STDFX_CONVREVERB_H
#define STDFX_CONVREVERB_H


#include "Buffer.h"
#include "Reverb.h"
#include "float_math.h"

/**
 * Implements a convolution reverb by multiplying in the frequency domain. Contains the FFT of an impulse
 * response and multiplies the incoming signal by this impulse response to produce a reverb'd sound.
 */
class ConvReverb : public Reverb {
private:
    Buffer<buf_f32pair_t> impulseResponse;
    Buffer<float> history;
    Buffer<buf_f32pair_t> fft_buf;
public:
    /**
     * Initializes the convolution reverb.
     *
     * @param impulseResponse Buffer which contains the FFT of the impulse response for this reverb.
     * @param history Must be the same length as the impulse response, and be filled with all zero values.
     * @param fft_buf Empty buffer which has the same length as the impulse response; acts as a buffer for computing the
     *                reverb.
     */
    ConvReverb(Buffer<buf_f32pair_t> impulseResponse, Buffer<float> history, Buffer<buf_f32pair_t> fft_buf);

    /**
     * Compute the reverb.
     *
     * @param inout Input and output array.
     * @param length Length of the array.
     */
    void tick(float *inout, uint32_t length) override;

};


#endif //STDFX_CONVREVERB_H
