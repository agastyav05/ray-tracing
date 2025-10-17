#include <iostream>
#include <fstream>
#include <vector>

#include "sphere.hpp"
#include "rect_prism.hpp"

inline bool in_world(Vec &p, Vec &world_start, Vec &world_end) {
    return p.x >= world_start.x && p.x <= world_end.x && p.y >= world_start.y && p.y <= world_end.y && p.z >= world_start.z && p.z <= world_end.z;
}

void render(Vec &world_start, Vec &world_end, Vec &screen_start, Vec &screen_end, Vec &eye, float step_size, std::vector<Obj *> &objects) {
    Vec screen_size = screen_end - screen_start + *(new Vec(1, 1, 1));
    std::cout << "Image size: " << screen_size.x << 'x' << screen_size.y << '\n';
    Vec image[(int) screen_size.x][(int) screen_size.y];
    int complete = 0;
    for (int x = 0; x < screen_size.x; x++) {
        for (int y = 0; y < screen_size.y; y++) {
            if (!complete || ((int) (100.0 * complete / (screen_size.x * screen_size.y)) != (int) (100.0 * (complete - 1) / (screen_size.x * screen_size.y)))) {
                std::cout << "\rRendering " << (int) (100.0 * (x * screen_size.y + y) / (screen_size.x * screen_size.y)) << '%';
            }
            complete++;
            std::cout.flush();
            Vec ray_dir = Vec(x + screen_start.x, y + screen_start.y, screen_start.z) - eye;
            ray_dir.set_mag(step_size);
            Vec cur = eye;
            bool done = false;
            while (in_world(cur, world_start, world_end)) {
                for (Obj *obj : objects) {
                    if (obj->in(cur)) {
                        image[x][y] = obj->color;
                        done = true;
                        break;
                    }
                }
                if (done) {
                    break;
                }
                cur += ray_dir;
            }
            if (!done) {
                image[x][y] = Vec();
            }
        }
    }
    std::cout << "\rRendering complete\n";
    std::ofstream f("image.ppm");
    f << "P3 " << screen_end.y - screen_start.y + 1 << ' ' << screen_end.x - screen_start.x + 1 << " 255\n";
    for (int x = 0; x <= screen_end.x - screen_start.x; x++) {
        for (int y = 0; y <= screen_end.y - screen_start.y; y++) {
            f << image[x][y].x << ' ' << image[x][y].y << ' '  << image[x][y].z << ' ';
        }
        f << '\n';
    }
}

int main() {
    Vec world_start = Vec();
    Vec world_end = Vec(1000, 1000, 100);
    Vec screen_start = Vec(436, 436, 25);
    Vec screen_end = Vec(563, 563, 25);
    Vec eye = Vec(500, 500, 0);
    const float step_size = 0.001;
    std::vector<Obj *> objects;
    // add objects
    render(world_start, world_end, screen_start, screen_end, eye, step_size, objects);
}