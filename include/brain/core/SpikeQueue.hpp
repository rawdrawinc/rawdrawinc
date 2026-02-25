#pragma once

#include <cstddef>
#include <deque>
#include <vector>

namespace brain::core {

struct ScheduledSpike {
  std::size_t target_neuron{};
  float weighted_signal{0.0F};
  std::size_t delivery_tick{};
};

class SpikeQueue {
 public:
  void Push(const ScheduledSpike& spike);
  [[nodiscard]] std::vector<ScheduledSpike> PopReady(std::size_t current_tick);

 private:
  std::deque<ScheduledSpike> queue_;
};

}  // namespace brain::core
