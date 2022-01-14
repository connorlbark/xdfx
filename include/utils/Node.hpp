//
// Created by Connor Barker on 1/14/22.
//

#ifndef STDFX_NODE_HPP
#define STDFX_NODE_HPP

#endif //STDFX_NODE_HPP

#include "Buffer.h"

class Node {
public:
    virtual buf_f32pair_t tick(buf_f32pair_t sample) { return sample; };
};