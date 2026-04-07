#pragma once

#include "common.hpp"
#include "vector.hpp"

class interval {
public:
  data_t min;
  data_t max;

  interval() : min(+inf), max(-inf) {}
  interval(data_t interval_min, data_t interval_max)
      : min(interval_min), max(interval_max) {}

  data_t size() { return max - min; }
  data_t clamp(data_t x) {
    if (x < min)
      return min;
    if (x > max)
      return max;
    return x;
  }
  bool contains(data_t x) const { return min <= x && x <= max; }
  bool surrounds(data_t x) const { return min < x && x < max; }

  static const interval empty;
  static const interval universe;
};

inline const interval interval::empty = interval(+inf, -inf);
inline const interval interval::universe = interval(-inf, +inf);
