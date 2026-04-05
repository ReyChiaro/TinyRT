#pragma once

#include "vector.hpp"
#include <iostream>

using color = vec3d;

/**
@param color: Each element of color vec3d should be double/float value between
[0,1]
*/
inline void write_color(std::ostream &out, const vec3d &color) {
  out << static_cast<int>(color.x() * 255) << " "
      << static_cast<int>(color.y() * 255) << " "
      << static_cast<int>(color.z() * 255) << std::endl;
}