#include <iostream>
#include <fstream>
#include <vector>

#include "light.hpp"
#include "sphere.hpp"
#include "rect_prism.hpp"

inline bool in_world(Vec &p, Vec &world_start, Vec &world_end) {
    return p.x >= world_start.x && p.x <= world_end.x && p.y >= world_start.y && p.y <= world_end.y && p.z >= world_start.z && p.z <= world_end.z;
}

void render(Vec &world_start, Vec &world_end, Color &background_color, Vec &screen_start, Vec &screen_end, Vec &eye, float step_size, std::vector<Obj *> &objects, std::vector<Light *> &lights) {
    Vec screen_size = screen_end - screen_start + *(new Vec(1, 1, 1));
    std::cout << "Image size: " << screen_size.x << 'x' << screen_size.y << '\n';
    Color image[(int) screen_size.x][(int) screen_size.y];
    int rendered = 0;
    for (int x = 0; x < screen_size.x; x++) {
        for (int y = 0; y < screen_size.y; y++) {
            if (!rendered || ((int) (100.0 * rendered / (screen_size.x * screen_size.y)) != (int) (100.0 * (rendered - 1) / (screen_size.x * screen_size.y)))) {
                std::cout << "\rRendering " << (int) (100.0 * (x * screen_size.y + y) / (screen_size.x * screen_size.y)) << '%';
            }
            rendered++;
            std::cout.flush();
            Vec ray_dir = Vec(x + screen_start.x, y + screen_start.y, screen_start.z) - eye;
            ray_dir.set_mag(step_size);
            Vec cur = eye;
            bool done = false;
            while (in_world(cur, world_start, world_end)) {
                for (Obj *obj : objects) {
                    if (obj->in(cur)) {
                        Vec norm = obj->norm(cur);
                        // TODO: handle multiple lights
                        Vec light_dir = lights[0]->loc - cur;
                        light_dir.set_mag(1);
                        float intensity = std::max(0.0l, lights[0]->brightness * (light_dir * norm));
                        Color color = obj->color;
                        color.scale(intensity);
                        image[x][y] = color;
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
                image[x][y] = background_color;
            }
        }
    }
    std::cout << "\rRendering complete\n";
    std::ofstream f("image.ppm");
    f << "P3 " << screen_size.y << ' ' << screen_size.x << " 255\n";
    for (int y = screen_size.y - 1; y >= 0; y--) {
        for (int x = 0; x < screen_size.x; x++) {
            f << image[x][y].r << ' ' << image[x][y].g << ' '  << image[x][y].b << ' ';
        }
        f << '\n';
    }
}

int main() {
    Vec world_start = Vec();
    Vec world_end = Vec(1000, 1000, 100);
    Color background_color = Color(50, 50, 50);
    Vec screen_start = Vec(436, 436, 25);
    Vec screen_end = Vec(563, 563, 25);
    Vec eye = Vec(500, 500, 0);
    // step_size defined in obj.hpp
    std::vector<Obj *> objects;
    objects.push_back(new Sphere(Vec(500, 500, 75), 50, Color(255, 0, 0)));
    objects.push_back(new RectPrism(Vec(450, 450, 25), Vec(500, 500, 125), Color(0, 0, 255)));
    objects.push_back(new RectPrism(Vec(530, 450, 25), Vec(540, 510, 35), Color(0, 128, 0)));
    std::vector<Light *> lights;
    lights.push_back(new Light(Vec(500, 600, -50)));
    render(world_start, world_end, background_color, screen_start, screen_end, eye, step_size, objects, lights);
}