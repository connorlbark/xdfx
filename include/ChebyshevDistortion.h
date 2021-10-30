//
// Created by Connor Barker on 10/5/21.
//

#ifndef STDFX_CHEBYSHEVDISTORTION_H
#define STDFX_CHEBYSHEVDISTORTION_H

#include "ModEffect.h"
#include "float_math.h"

class ChebyshevDistortion : public ModEffect {
private:
    float *coefficients;
    int coefficients_length;

    float h1(float x) { return x; }

    float h2(float x) { return 2.f * fastpow2f(x) - 1; }

    float h3(float x) { return 4.f * fasterpowf(x, 3.f) - 3.f * x; }

    float h4(float x) { return 8.f * fasterpowf(x, 4.f) - 8.f * fasterpow2f(x) + 1; }

    float h5(float x) { return 16.f * fasterpowf(x, 5.f) - 20.f * fasterpowf(x, 3.f) + 5.f * x; }

    float h6(float x) { return 32.f * fasterpowf(x, 6.f) - 48.f * fasterpowf(x, 4.f) + 18.f * fastpow2f(x) - 1; }

    float h7(float x) {
        return 64.f * fasterpowf(x, 7.f) - 112.f * fasterpowf(x, 5.f) + 56.f * fasterpowf(x, 3.f) - 7.f * x;
    }

    float h8(float x) {
        return 128.f * fasterpowf(x, 8.f) - 256.f * fasterpowf(x, 6.f) + 160.f * fasterpowf(x, 4.f) -
               32.f * fastpow2f(x) + 1;
    }

    float h9(float x) {
        return 256.f * fasterpowf(x, 9.f) - 576.f * fasterpowf(x, 7.f) + 432.f * fasterpowf(x, 5.f) -
               120.f * fasterpowf(x, 3.f) + 9.f * x;
    }

    float h10(float x) {
        return 512.f * fasterpowf(x, 10.f) - 1280.f * fasterpowf(x, 8.f) + 1120.f * fasterpowf(x, 6.f) -
               400.f * fasterpowf(x, 4.f) + 50.f * fastpow2f(x) - 1.f;
    }


    float coefficient(int i) {
        return coefficients[i];
    }

    float apply(float x) {
        if (x < .001f) {
            return x;
        }

        float sum = 0.f;

        for (int i = 0; i < 10; i++) {
            float c = coefficient(i) * coefficient_scalar(i);

            if (c < .001f) {
                continue;
            }

            switch (i) {
                case 0:
                    sum += c * x;
                    break;
                case 1:
                    sum += c * h2(x);
                    break;
                case 2:
                    sum += c * h3(x);
                    break;
                case 3:
                    sum += c * h4(x);
                    break;
                case 4:
                    sum += c * h5(x);
                    break;
                case 5:
                    sum += c * h6(x);
                    break;
                case 6:
                    sum += c * h7(x);
                    break;
                case 7:
                    sum += c * h8(x);
                    break;
                case 8:
                    sum += c * h9(x);
                    break;
                case 9:
                    sum += c * h10(x);
                    break;
                default:
                    break;
            }
        }

        return sum;
    }

protected:


    virtual float coefficient_scalar(int i) {



        if (i == 0) {
            return 1.f-this->depth/2.f;
        }


        return this->depth*(1-(this->time - (float(i)/5.f)));
    }

public:
    ChebyshevDistortion(float *coefficients, int coefficients_length) : coefficients(coefficients),
                                                                        coefficients_length(coefficients_length) {

    }

    virtual void tick(const float *in, float *out, uint32_t inp_length) {
        const float *mx = in;
        float *__restrict my = out;
        const float *my_e = my + 2 * inp_length;

        for (; my != my_e;) {
            //*(my++) = clip1m1f(*(mx++));
            *(my++) = clip1m1f(this->apply(*(mx++)));


        }
    }


};


#endif //STDFX_CHEBYSHEVDISTORTION_H
