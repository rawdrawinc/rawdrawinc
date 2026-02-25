#include "brain/core/SpikeQueue.hpp"

#include <algorithm>

namespace brain::core {

void SpikeQueue::Push(const ScheduledSpike& spike) {
  queue_.push_back(spike);
}

std::vector<ScheduledSpike> SpikeQueue::PopReady(const std::size_t current_tick) {
  std::vector<ScheduledSpike> ready;

  auto partition_point = std::stable_partition(queue_.begin(), queue_.end(), [current_tick](const ScheduledSpike& s) {
    return s.delivery_tick > current_tick;
  });

  while (partition_point != queue_.end()) {
    ready.push_back(*partition_point);
    partition_point = queue_.erase(partition_point);
  }

  return ready;
}

}  // namespace brain::core
