#ifndef VEC_HPP
#define VEC_HPP
#include "vec.hpp"
#endif

struct Light {
    Vec loc;
    float brightness;

    Light(Vec loc_, float brightness_ = 1.0) {
        loc = loc_;
        brightness = brightness_;
    }
};