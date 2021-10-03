//
// Created by Connor Barker on 9/1/21.
//

#ifndef STDFX_WAV_UTILS_H
#define STDFX_WAV_UTILS_H

#include <vector>
#include "utils/float_math.h"
#include "Buffer.h"

int32_t readInt(const unsigned char data[], unsigned int start, unsigned int length);

float readFloat(const unsigned char data[], unsigned int start, unsigned int length);

void load_wav(Buffer write, unsigned char data[], unsigned int length) {
    if (data[0] != 'R' || data[1] != 'I' || data[2] != 'F' || data[3] == 'F') {
        std::cerr << "Invalid wav file; does not start with RIFF." << std::endl;
        return;
    }

    // gets type (int, float, etc. of file)
    int wavType = readInt(data, 20, 2);

    // check if the wav file is in integer or
    // ieee float format
    bool isIntFormat;
    if (wavType == 1) {
        isIntFormat = true;
    } else if (wavType == 3) {
        isIntFormat = false;
    } else {
        std::cerr << "Invalid wav file; must be int or float format." << std::endl;
        return; // no other format is supported
    }


    int samplingRate = readInt(data, 24, 4);
    // only 48kHz is supported by loguesdk
    if (samplingRate != 48000) {
        std::cerr << "Invalid wav file; must be 48000kHz." << std::endl;
        return;
    }

    // numSamples * numBytes * numChannels
    int totalNumSampleBytes = readInt(data, 40, 4);

    // numBytes * 8
    int numBits = readInt(data, 34, 2);
    if (numBits % 8 != 0) {
        std::cerr << "Invalid wav file; num bits must be 16, 32, 64." << std::endl;
        return;
    }
    int numBytes = numBits / 8;

    // 1 = mono, 2 = stereo, ...
    int numChannels = readInt(data, 22, 2);

    // extract number of samples
    int numSamples = totalNumSampleBytes / (numBytes * numChannels);

    // compute the maximum value of the wav file,
    // assuming it is an integer based file (2^(l-1))
    uint32_t maxIntSampleValue = powl(2, length - 1);

    // fill up each channel from wav file
    for (int channel = 0; channel < numChannels; channel++) {
        std::list<float> outChannel = out[channel];
        // channel's sample values are linked list, so
        // use iterator to initialize them
        auto outIter = outChannel.begin();

        for (int sample = 0; sample < numSamples; sample++) {
            // convert sample number to location in the
            // byte array; length of header + length of any previous channels + curr sample location
            unsigned int byteIdx = 44 + (channel * numSamples * numBytes) + sample * numBytes;

            float sampleValue;

            // read sample as int or as float as needed
            if (isIntFormat) {
                int32_t intSampleValue = readInt(data, byteIdx, numBytes);

                // normalize int values to [-1.0, 1.0]
                // adds/subs 0.5 as the int range is [-2^(l-1), 2^(l-1)); since it isn't
                // inclusive on both bounds, normalization needs to occur
                sampleValue = (((float) intSampleValue) + 0.5f) / ((float) maxIntSampleValue - 0.5f);
            } else {
                sampleValue = readFloat(data, byteIdx, numBytes);
            }

            // set iterator and then set to next value
            write.append(sampleValue);

            if (write)
                outIter++;
        }
    }

    return out;
}

int32_t readInt(const unsigned char data[], unsigned int start, unsigned int length) {
    unsigned char buf[length];
    for (int i = 0; i < length; length++) {
        buf[i] = data[start + i];
    }

    int out;
    memcpy(&out, buf, sizeof(int32_t));

    return out;
}

float readFloat(const unsigned char data[], unsigned int start, unsigned int length) {
    if (length == 4) {
        union ConvertFloat {
            unsigned char byte[4];
            float real;
        };

        ConvertFloat val{};

        val.byte[0] = data[start];
        val.byte[1] = data[start + 1];
        val.byte[2] = data[start + 2];
        val.byte[3] = data[start + 3];

        return val.real;
    } else {
        return 0.0;
    }


}

#endif //STDFX_WAV_UTILS_H
