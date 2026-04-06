#pragma once

#include "hittable.hpp"
#include "interval.hpp"
#include "vector.hpp"
#include <memory>
#include <vector>

class hittable_list : public hittable {
public:
  std::vector<std::shared_ptr<hittable>> objects{};

  hittable_list() = default;
  hittable_list(std::shared_ptr<hittable> object) { add(object); }

  void clear() { objects.clear(); }

  void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

  bool hit(const ray &r, const interval ray_t, hit_info &info) const override {
    hit_info temp_info;
    data_t cloest_t = ray_t.max;
    bool is_hit = false;

    for (const auto &obj : objects) {
      if (obj->hit(r, ray_t, temp_info)) {
        is_hit = true;
        if (temp_info.t < cloest_t) {
          cloest_t = temp_info.t;
          info = temp_info;
        }
      }
    }

    return is_hit;
  }
};