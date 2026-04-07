#pragma once

#include "color.hpp"
#include "common.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "vector.hpp"

class camera {
public:
  int num_samplers_per_pixel;

  void render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

    for (int h = 0; h < img_h; h++) {
      std::clog << "\rScanlines: " << h << ' ' << std::flush;
      for (int w = 0; w < img_w; w++) {
        auto pixel_color = color(0, 0, 0);
        for (auto _ = 0; _ < num_samplers_per_pixel; _ += 1) {
          ray r = get_ray(w, h);
          pixel_color += ray_color(r, world);
        }

        write_color(std::cout, pixel_color, num_samplers_per_pixel);
      }
    }

    std::clog << "\nDone." << std::endl;
    ;
  }

private:
  point3d _center;      // Camera center
  point3d _pixel00_loc; // Location of pixel 0, 0
  vec3d _pixel_delta_u; // Offset to pixel to the right
  vec3d _pixel_delta_v; // Offset to pixel below

  void initialize() {
    _center = point3d(0, 0, 0);
    num_samplers_per_pixel = 10;

    // Determine viewport dimensions.
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(img_w) / img_h);

    // Calculate the vectors across the horizontal and down the vertical
    // viewport edges.
    auto viewport_u = vec3d(viewport_width, 0, 0);
    auto viewport_v = vec3d(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    _pixel_delta_u = viewport_u / img_w;
    _pixel_delta_v = viewport_v / img_h;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        _center - vec3d(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    _pixel00_loc =
        viewport_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);
  }

  color ray_color(const ray &r, const hittable &world) const {
    hit_info rec;

    if (world.hit(r, interval(0, inf), rec)) {
      return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3d unit_direction = normalize(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }

  ray get_ray(int w, int h) const {
    auto pix_center = _pixel00_loc + w * _pixel_delta_u + h * _pixel_delta_v;
    auto pixel = pix_center + sample_pixel();
    return ray(_center, pixel - _center);
  }

  point3d sample_pixel() const {
    auto px = random_number() - 0.5;
    auto py = random_number() - 0.5;
    return px * _pixel_delta_u + py * _pixel_delta_v;
  }
};