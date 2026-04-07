#pragma once

#include "vector.hpp"
#include <algorithm>
#include <limits>
#include <random>

const auto aspect_ratio = 16.0 / 9.0;
const auto img_w = 512;
const auto sphere_center = point3d(0, 0, -1);
const auto sphere_radius = 0.5;
const auto inf = std::numeric_limits<data_t>::infinity();
const auto img_h = std::max(static_cast<int>(img_w / aspect_ratio), 1);

inline data_t random_number() {
  static std::uniform_real_distribution<data_t> dist(0.0, 1.0);
  static std::default_random_engine e;
  return dist(e);
}