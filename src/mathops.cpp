//
// Created by Connor Barker on 8/31/21.
//

#include "../include/mathops.h"

#include "utils/float_math.h"
/*
void convolve(const std::vector<float>& impulseResponse, float *x, float *y, int n) {
    for (int i = 0; i < n; i++) {
        float yi = 0.0;
        for (int j = 0; j < impulseResponse.size(); j++) {
            yi += impulseResponse[impulseResponse.size()-j-1] * x[i-j];
        }
        *(y+i) = yi;
    }
}*/

/*
FFT Psuedocode

   X0,...,N−1 ← ditfft2(x, N, s):             DFT of (x0, xs, x2s, ..., x(N-1)s):
    if N = 1 then
        X0 ← x0                                      trivial size-1 DFT base case
    else
        X0,...,N/2−1 ← ditfft2(x, N/2, 2s)             DFT of (x0, x2s, x4s, ...)
        XN/2,...,N−1 ← ditfft2(x+s, N/2, 2s)           DFT of (xs, xs+2s, xs+4s, ...)
        for k = 0 to N/2−1 do                        combine DFTs of two halves into full DFT:
            p ← Xk
            q ← exp(−2πi/N k) Xk+N/2
            Xk ← p + q
            Xk+N/2 ← p − q
        end for
    end if
 */
/*void fft(Buffer in, Buffer out, bool channel, int start, int end) {

    int length = end - start;

    if (in.length() == 1) {
        out.append(in.left(0), in.right(0));
        return;
    }

    int mid = length/2;
    fft(in, out, channel, start, start+mid); // fill out from [0,n/2)
    fft(in, out, channel, start+mid, end); // fill out from [n/2, n)

    for (int k = 0; k < mid; k++) {
        float x1 = (channel?out.right(start+k):out.left(start+k));
        float x2 = (channel?out.right(start+k+mid):out.left(start+k+mid));
        float qr = fastcosf(-M_PI_2 * ((float)k / (float)length)) * x2;
        float qc = fastsinf(-M_PI_2 * ((float)k / (float)length)) * x2;


        out.left(start+k) = x1+qr;
        out.right(start+k) = qc;

        out.left(start+k+mid) = x1-qr;
        out.right(start+k+mid) = -qc;
    }
}

void fft(Buffer in, Buffer out, bool channel) {
    int length = in.length();

    return fft(in, out, channel, 0, length);
}

void comp_mult(Buffer x1out, Buffer x2) {
    int length = x1out.length();

    for (int i = 0; i < length; i++) {
        float x1r = x1out.left(i);
        float x1c = x1out.right(i);

        float x2r = x2.left(i);
        float x2c = x2.right(i);

        float outr = (x1r*x2r - x1c * x2c);
        float outc = (x1r*x2c + x2r * x1c);

        x1out.set(i, outr, outc);
    }
}*/