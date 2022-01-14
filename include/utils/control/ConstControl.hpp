//
// Created by Connor Barker on 1/14/22.
//

#ifndef STDFX_CONSTCONTROL_HPP
#define STDFX_CONSTCONTROL_HPP

#endif //STDFX_CONSTCONTROL_HPP
#include "Control.hpp"

class ConstControl: public Control {
private:
    int val;
public:
    ConstControl(int val) : val(val) {};

    int get() {return val;}
};