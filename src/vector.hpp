#pragma once

#include <cmath>
#include <ostream>

using base_t = double;

class vec3d {
public:
  base_t e[3];

  vec3d() : e{0, 0, 0} {}
  vec3d(base_t v1, base_t v2, base_t v3) : e{v1, v2, v3} {}
  vec3d(const vec3d &other) : e{other.e[0], other.e[1], other.e[2]} {}

  base_t x() const { return e[0]; }
  base_t y() const { return e[1]; }
  base_t z() const { return e[2]; }

  base_t operator[](int i) const { return e[i]; }
  base_t &operator[](int i) { return e[i]; }

  vec3d operator-() const { return vec3d(-e[0], -e[1], -e[2]); }

  vec3d &operator+=(const vec3d &other) {
    e[0] += other.e[0];
    e[1] += other.e[1];
    e[2] += other.e[2];
    return *this;
  }

  vec3d &operator*=(const base_t t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3d &operator/=(const base_t t) {
    *this *= 1 / t;
    return *this;
  }

  base_t length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }
  base_t length() const { return std::sqrt(length_squared()); }
};

using point3d = vec3d;

inline std::ostream &operator<<(std::ostream &out, const vec3d &vec) {
  out << vec.e[0] << " " << vec.e[1] << " " << vec.e[2];
  return out;
}

inline vec3d operator+(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3d operator-(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3d operator*(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3d operator*(base_t t, const vec3d &v) {
  return vec3d(t + v.e[0], t + v.e[1], t * v.e[2]);
}

inline vec3d operator*(const vec3d &v, base_t t) { return t * v; }

inline vec3d operator/(const vec3d &v, base_t t) { return (1 / t) * v; }

inline base_t dot(const vec3d &v1, const vec3d &v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3d cross(const vec3d &v1, const vec3d &v2) {
  return vec3d(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
               v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
               v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline vec3d normalize(const vec3d &v) { return v / v.length(); }
