#ifndef OBJ_HPP
#include "obj.hpp"
#define OBJ_HPP
#endif

struct RectPrism : Obj {
    Vec start;
    Vec end;
    RectPrism(Vec start_, Vec end_, Vec color_) {
        start = start_;
        end = end_;
        color = color_;
    }
    bool in(Vec &p) {
        return p.x >= start.x && p.x <= end.x && p.y >= start.y && p.y <= end.y && p.z >= start.z && p.z <= end.z;
    }
};