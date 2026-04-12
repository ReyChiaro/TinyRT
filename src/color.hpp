#pragma once

#include "interval.hpp"
#include "types.hpp"
#include "vector.hpp"
#include <cmath>
#include <iostream>

inline auto linear_to_gamma(data_t linear_color) {
  return linear_color < 0 ? 0 : std::sqrt(linear_color);
}

/**
@param color: Each element of color vec3d should be double/float value between
[0,1]
*/
inline void write_color(std::ostream &out, const vec3d &color,
                        const int num_samplers_per_pixel) {
  auto r = color.x();
  auto g = color.y();
  auto b = color.z();

  auto scale = 1.0 / num_samplers_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  interval color_range(0, 1);
  out << static_cast<int>(color_range.clamp(r) * 255) << " "
      << static_cast<int>(color_range.clamp(g) * 255) << " "
      << static_cast<int>(color_range.clamp(b) * 255) << std::endl;
}