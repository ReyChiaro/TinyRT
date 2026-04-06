#pragma once

#include "vector.hpp"
#include <limits>

const auto aspect_ratio = 16.0 / 9.0;
const auto img_w = 512;
const auto sphere_center = point3d(0, 0, -1);
const auto sphere_radius = 0.5;
const auto inf = std::numeric_limits<data_t>::infinity();
