#ifndef OBJ_HPP
#define OBJ_HPP
#include "obj.hpp"
#endif

struct Sphere : Obj {
    Vec c;
    long double r;

    Sphere(Vec c_, long double r_, Color color_) {
        assert(r_ > 0);
        c = c_;
        r = r_;
        color = color_;
    }

    bool in(Vec &p) {
        long double x_dist = abs(c.x - p.x), y_dist = abs(c.y - p.y), z_dist = abs(c.z - p.z);
        return sqrt(x_dist * x_dist + y_dist * y_dist + z_dist * z_dist) <= r;
    }

    Vec norm(Vec &p) {
        Vec result = p - c;
        result.set_mag(1);
        return result;
    }
};