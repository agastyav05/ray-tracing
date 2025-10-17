#include <cassert>

#ifndef OBJ_HPP
#define OBJ_HPP
#include "obj.hpp"
#endif

struct RectPrism : Obj {
    Vec start;
    Vec end;

    RectPrism(Vec start_, Vec end_, Color color_) {
        start = start_;
        end = end_;
        color = color_;
    }

    bool in(Vec &p) {
        return p.x >= start.x && p.x <= end.x && p.y >= start.y && p.y <= end.y && p.z >= start.z && p.z <= end.z;
    }

    Vec norm(Vec &p) {
        if (abs(p.x - start.x) <= step_size) {
            return Vec(-1, 0, 0);
        }
        if (abs(p.x - end.x) <= step_size) {
            return Vec(1, 0, 0);
        }
        if (abs(p.y - start.y) <= step_size) {
            return Vec(0, -1, 0);
        }
        if (abs(p.y - end.y) <= step_size) {
            return Vec(0, 1, 0);
        }
        if (abs(p.z - start.z) <= step_size) {
            return Vec(0, 0, -1);
        }
        if (abs(p.z - end.z) <= step_size) {
            return Vec(0, 0, 1);
        }
        assert(false);
    }
};