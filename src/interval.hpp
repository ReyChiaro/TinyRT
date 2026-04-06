#pragma once

#include "constants.hpp"
#include "vector.hpp"

class interval {
public:
  data_t min;
  data_t max;

  interval() : min(+inf), max(-inf) {}
  interval(data_t interval_min, data_t interval_max)
      : min(interval_min), max(interval_max) {}

  data_t size() { return max - min; }
  bool contains(double x) const { return min <= x && x <= max; }
  bool surrounds(double x) const { return min < x && x < max; }

  static const interval empty;
  static const interval universe;
};

inline const interval interval::empty = interval(+inf, -inf);
inline const interval interval::universe = interval(-inf, +inf);
