#pragma once

#include "ray.hpp"
#include "vector.hpp"

struct hit_info {
  point3d point;
  vec3d normal;
  data_t t;

  // The direction ray, true for outward and false otherwise.
  bool front_face;

  void set_front_face(const ray &r, const vec3d &outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0.0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, const data_t t_min, const data_t t_max,
                   hit_info &info) const = 0;
};