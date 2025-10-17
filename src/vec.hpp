#include <cmath>
#include <cassert>

struct Vec {
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

    Vec operator+(Vec &v) {
        return Vec(x + v.x, y + v.y, z + v.z);
    }

    Vec &operator+=(Vec &v) {
        x += v.x, y += v.y, z += v.z;
        return *this;
    }

    Vec operator-(Vec &v) {
        return Vec(x - v.x, y - v.y, z - v.z);
    }

    long double operator*(Vec &v) {
        return x * v.x + y * v.y + z * v.z;
    }

    long double mag() {
        return sqrt(x * x + y * y + z * z);
    }

    void set_mag(long double mag_) {
        long double old_mag = mag();
        x /= (old_mag / mag_), y /= (old_mag / mag_), z /= (old_mag / mag_);
    }

    void make_unit() {
        long double mag_ = mag();
        assert(mag_);
        x /= mag_, y /= mag_, z /= mag_;
    }
};