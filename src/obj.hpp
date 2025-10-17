#include "vec.hpp"

struct Obj {
    Vec color;

    virtual bool in(Vec &p) {
        return false;
    }
};