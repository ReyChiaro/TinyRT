#pragma once

#include "vector.hpp"

class ray {
private:
  point3d _origin;
  vec3d _direction;

public:
  ray() = default;
  ray(const point3d &origin, const vec3d &direction) {
    this->_origin = origin;
    this->_direction = direction;
  }

  const point3d &origin() const { return this->_origin; }
  const vec3d &direction() const { return this->_direction; }

  point3d at(data_t t) const{ return _origin + t * _direction; }
};