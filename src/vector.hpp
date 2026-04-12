#pragma once

#include "types.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>

class vec3d {
public:
  data_t e[3];

  vec3d() : e{0, 0, 0} {}
  vec3d(data_t v1, data_t v2, data_t v3) : e{v1, v2, v3} {}
  vec3d(const vec3d &other) : e{other.e[0], other.e[1], other.e[2]} {}

  data_t x() const { return e[0]; }
  data_t y() const { return e[1]; }
  data_t z() const { return e[2]; }

  data_t operator[](int i) const { return e[i]; }
  data_t &operator[](int i) { return e[i]; }

  vec3d operator-() const { return vec3d(-e[0], -e[1], -e[2]); }

  vec3d &operator+=(const vec3d &other) {
    e[0] += other.e[0];
    e[1] += other.e[1];
    e[2] += other.e[2];
    return *this;
  }

  vec3d &operator*=(const data_t t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3d &operator/=(const data_t t) {
    *this *= 1 / t;
    return *this;
  }

  data_t length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }
  data_t length() const { return std::sqrt(length_squared()); }

  static vec3d random() {
    return vec3d(random_number(), random_number(), random_number());
  }

  static vec3d random(data_t min, data_t max) {
    return vec3d(random_number(min, max), random_number(min, max),
                 random_number(min, max));
  }
};

inline std::ostream &operator<<(std::ostream &out, const vec3d &vec) {
  out << vec.e[0] << " " << vec.e[1] << " " << vec.e[2];
  return out;
}

inline vec3d operator+(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3d operator+(const data_t &t, const vec3d &v) {
  return vec3d(t + v.e[0], t + v.e[1], t + v.e[2]);
}

inline vec3d operator+(const vec3d &v, const data_t &t) { return t + v; }

inline vec3d operator-(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3d operator*(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3d operator*(data_t t, const vec3d &v) {
  return vec3d(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3d operator*(const vec3d &v, data_t t) { return t * v; }

inline vec3d operator/(const vec3d &v, data_t t) { return (1 / t) * v; }

inline data_t dot(const vec3d &v1, const vec3d &v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3d cross(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
               v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
               v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline vec3d normalize(const vec3d &v) { return v / v.length(); }

inline vec3d random_in_unit_sphere() {
  while (true) {
    auto p = vec3d::random(-1, 1);
    if (p.length() > 1) {
      continue;
    }
    return p;
  }
}

inline vec3d random_unit_vector() { return normalize(random_in_unit_sphere()); }

inline vec3d random_on_hemisphere(const vec3d &normal) {
  auto unit_p = random_unit_vector();
  return dot(unit_p, normal) > 0 ? unit_p : -unit_p;
}

using point3d = vec3d;
using color = vec3d;
