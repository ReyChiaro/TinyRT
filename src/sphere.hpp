#pragma once

#include "hittable.hpp"
#include "interval.hpp"
#include "vector.hpp"
#include <cmath>

class sphere : public hittable {
private:
  point3d _center;
  data_t _radius;

public:
  sphere(const point3d &center, const data_t radius)
      : _center(center), _radius(radius) {}

  bool hit(const ray &r, const interval ray_t, hit_info &info) const override {
    vec3d oc = _center - r.origin();

    auto a = dot(r.direction(), r.direction());
    auto h = dot(r.direction(), oc);
    auto c = dot(oc, oc) - _radius * _radius;
    auto delta = h * h - a * c;

    if (delta < 0)
      return false;

    auto sqrt_delta = std::sqrt(delta);

    auto root = (h - sqrt_delta) / a;
    if (root <= ray_t.min || root >= ray_t.max) {
      root = (h + sqrt_delta) / a;
      if (root <= ray_t.min || root >= ray_t.max) {
        return false;
      }
    }

    info.t = root;
    info.point = r.at(info.t);
    info.set_front_face(r, (info.point - _center) / _radius);

    return true;
  }
};