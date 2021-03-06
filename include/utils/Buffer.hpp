//
// Created by Connor Barker on 9/1/21.
//

#ifndef STDFX_BUFFER_HPP
#define STDFX_BUFFER_HPP

#include "float_math.h"


// a Buffer is an array of audio samples with a variable number of samples;
// optimized for adding values at beginning and end
template <class F>
class Buffer {
private:
    int length_;
    int ram_start_idx_;

    F *ram_;
    int ram_length_;
private:
    // converts a user-facing sample index to an address in 'ram'
    // which corresponds to the left value
    int ram_addr_(int buf_idx) const {
        return (ram_start_idx_ + buf_idx) % this->length_;
    }

    // bounds some index to be within the boundaries of ram for one channel;
    // will wrap around, e.g. -1 -> max-1, max+1 -> 1
    int wrap_channel_ram_addr(int idx) const {
        int max = this->ram_length_;

        if (idx < 0) {
            return max + idx;
        } else if (idx >= max) {
            return idx - max;
        }

        return idx;
    }

public:
    Buffer(F *ram, int ram_length) : ram_length_(ram_length),
                                              ram_start_idx_(0), length_(0),
                                              ram_(ram) {
    }

    Buffer(F *ram, int ram_length, int data_length) :
            ram_length_(ram_length),
            ram_start_idx_(0), length_(data_length),
            ram_(ram) {
    }


    int length() const {
        return this->length_;
    }

    // puts new value at the beginning, deletes last value. length stays
    // the same, but the data has all shifted one index forward. this
    // operation is constant time.
    void forward_shift(F newVal) {
        // basic idea: keep length the same, but move the ram's index back and
        // write a new value at the start location. The last value isn't technically
        // always deleted, but it will no longer be within the 'length' attribute, so
        // it will be ignored.

        // move start back to accommodate new value
        int new_start = this->wrap_channel_ram_addr(this->ram_start_idx_ - 1);
        // set start value
        this->ram_[new_start] = newVal;
    }

    // puts new value(s) at at the end of each channel, deletes first value.
    // length stays the same, but the data has shifted. this operation runs
    // in constant time.
    void backward_shift(F newVal) {
        // move start up one value, so the start value is now gone, but the last value
        // is gibberish; must be set
        int new_start = this->wrap_channel_ram_addr(this->ram_start_idx_ + 1);
        this->ram_start_idx_ = new_start;

        // set value at end
        this->ram_[this->ram_addr_(this->length_ - 1)] = newVal;
    }

    void fill(float val) {
        while (!this->is_full()) {
            this->append(val);
        }
    }

    F &operator[](int i) const {
        return this->ram_[this->ram_addr_(i)];
    };

    void prepend(F val) {
        // if there is no more room, then we have to do a forward shift
        // as we cannot grow this->length_
        if (length_ == this->length()) {
            this->forward_shift(val);
            return;
        }

        // make usable sample space larger to accommodate new value
        this->length_++;

        // compute new start idx (shifted back, as to add a new value)
        this->ram_start_idx_ = this->wrap_channel_ram_addr(this->ram_start_idx_ - 1);

        // set new prepended value
        this->ram_[ram_start_idx_] = val;
    }


    void append(F val) {
        // if there is no more room, then we have to do a backward shift
        // as we cannot grow this->length_
        if (this->is_full()) {
            this->backward_shift(val);
            return;
        }

        // make usable sample space larger to accommodate new value
        this->length_++;

        // set new prepended value
        this->ram_[ram_start_idx_] = val;
    }

    bool is_full() const {
        return this->length_ >= this->ram_length_;
    }

    const F *raw() const {
        return this->ram_;
    }

    void clear() {
        this->ram_start_idx_ = 0;
        this->length_ = 0;
    }
};


#endif //STDFX_BUFFER_HPP
