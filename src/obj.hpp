#ifndef VEC_HPP
#define VEC_HPP
#include "vec.hpp"
#endif
#include "color.hpp"

const float step_size = 0.001;

struct Obj {
    Color color;

    virtual bool in(Vec &p) {
        return false;
    }

    virtual Vec norm(Vec &p) {
        return Vec();
    }
};