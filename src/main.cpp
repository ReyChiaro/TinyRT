#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "vector.hpp"
#include <memory>

int main() {
  hittable_list world;
  world.add(std::make_shared<sphere>(point3d(0.1, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point3d(-0.1, -0.2, -0.5), 0.2));
  world.add(std::make_shared<sphere>(point3d(0, -100.5, -1), 100));

  camera cam;
  cam.render(world);

  return 0;
}
