#include "color.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vector.hpp"
#include <iostream>
#include <limits>
#include <memory>
#include <thread>

auto aspect_ratio = 16.0 / 9.0;
auto img_w = 512;
auto sphere_center = point3d(0, 0, -1);
auto sphere_radius = 0.5;
auto inf = std::numeric_limits<data_t>::infinity();

color ray_color(const ray &r, const hittable_list &world) {
  hit_info info;
  if (world.hit(r, 0, inf, info)) {
    return color(0.5 * (info.normal + 1.0));
  }

  // Default background
  vec3d direction = normalize(r.direction());
  auto alpha = 0.5 * (direction.y() + 1.0);
  return (1 - alpha) * color(1.0, 1.0, 1.0) + alpha * color(0.5, 0.7, 1.0);
}

using namespace std::chrono_literals;
int main() {

  /* -------- Image -------- */
  int img_h = static_cast<int>(img_w / aspect_ratio);
  img_h = img_h < 1 ? 1 : img_h;

  /* -------- Camera -------- */
  // Note that right-hand coordinate system is used.
  data_t focal_length = 1.0;
  data_t viewport_h = 2.0;
  data_t viewport_w = viewport_h * (data_t(img_w) / img_h);
  auto camera_center = point3d(0, 0, 0);

  // Viewport
  auto vp_u = point3d(viewport_w, 0, 0);
  auto vp_v = point3d(0, -viewport_h, 0);

  auto pix_du = vp_u / img_w;
  auto pix_dv = vp_v / img_h;

  std::clog << pix_du << std::endl;
  std::clog << pix_dv << std::endl;

  auto vp_upper_left =
      camera_center - vec3d(0, 0, focal_length) - vp_u / 2 - vp_v / 2;

  auto pix00 = vp_upper_left + 0.5 * (pix_du + pix_dv);

  /* -------- Render -------- */

  auto world = hittable_list();
  world.add(std::make_shared<sphere>(point3d(-0.1, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point3d(0.2, -0.1, -0.5), 0.1));
  world.add(std::make_shared<sphere>(point3d(0, -100.5, -1), 100));

  std::cout << "P3" << std::endl;
  std::cout << img_w << " " << img_h << std::endl;
  std::cout << 255 << std::endl;

  for (unsigned int h = 0; h < img_h; h += 1) {
    std::clog << "\rScanlines: " << (h + 1) << " " << std::flush;
    std::this_thread::sleep_for(0.1ms);
    for (unsigned int w = 0; w < img_w; w += 1) {
      auto pix = pix00 + w * pix_du + h * pix_dv;
      auto ray_direction = pix - camera_center;
      auto r = ray(camera_center, ray_direction);

      auto pix_color = ray_color(r, world);
      write_color(std::cout, pix_color);
    }
  }
  std::clog << "\nDone." << std::endl;

  return 0;
}
