#include <cmath>
#include <cassert>
#include <string>

class Vec {
    public:
        long double x;
        long double y;
        long double z;
        Vec() {
            x = 0;
            y = 0;
            z = 0;
        }
        Vec(long double x_, long double y_, long double z_) {
            x = x_;
            y = y_;
            z = z_;
        }
        long double dot(Vec* v) {
            return x * v->x + y * v->y + z * v->z;
        }
        long double mag() {
            return sqrt(x * x + y * y + z * z);
        }
        Vec* make_unit() {
            assert(mag());
            return new Vec(x / mag(), y / mag(), z / mag());
        }
        std::string to_string() {
            return "<" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ">";
        }
};