#pragma once

#include <cstddef>

namespace brain::core {

struct Synapse {
  std::size_t pre_index{};
  std::size_t post_index{};
  float weight{0.0F};
  int delay_ticks{1};
};

}  // namespace brain::core
