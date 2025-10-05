#include <math.h>
#include <iostream>

#include "vec.hpp"

int main() {
    Vec v = Vec(1, 2, 3);
    v = *v.make_unit();
    std::cout << "a\n";
    std::cout << v.to_string() << '\n';
}