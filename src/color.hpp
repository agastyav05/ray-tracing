#include <cmath>
#include <cassert>

struct Color {
    short r;
    short g;
    short b;

    Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    Color(short r_, short g_, short b_) {
        r = r_;
        g = g_;
        b = b_;
    }

    void scale(float c) {
        r = (short) (r * c);
        g = (short) (g * c);
        b = (short) (b * c);
    }
};