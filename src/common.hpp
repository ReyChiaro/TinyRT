#pragma once

#include "vector.hpp"
#include <algorithm>
#include <limits>

const auto aspect_ratio = 16.0 / 9.0;
const auto img_w = 720;
const auto sphere_center = point3d(0, 0, -1);
const auto sphere_radius = 0.5;
const auto inf = std::numeric_limits<data_t>::infinity();
const auto img_h = std::max(static_cast<int>(img_w / aspect_ratio), 1);
const auto gamma = 2;
