#pragma once

#include "types.hpp"
#include <random>

inline data_t random_number() {
  static std::uniform_real_distribution<data_t> dist(0.0, 1.0);
  static std::default_random_engine e;
  return dist(e);
}

inline data_t random_number(data_t min, data_t max) {
  static std::uniform_real_distribution<data_t> dist(min, max);
  static std::default_random_engine e;
  return dist(e);
}