#include "brain/core/SpikeQueue.hpp"

#include <algorithm>
#include <iterator>

namespace brain::core {

void SpikeQueue::Push(const ScheduledSpike& spike) {
  queue_.push_back(spike);
}

std::vector<ScheduledSpike> SpikeQueue::PopReady(const std::size_t current_tick) {
  auto partition_point = std::stable_partition(queue_.begin(), queue_.end(), [current_tick](const ScheduledSpike& s) {
    return s.delivery_tick > current_tick;
  });

  std::vector<ScheduledSpike> ready;
  if (partition_point != queue_.end()) {
    ready.reserve(static_cast<std::size_t>(std::distance(partition_point, queue_.end())));
    std::move(partition_point, queue_.end(), std::back_inserter(ready));
    queue_.erase(partition_point, queue_.end());
  }

  return ready;
}

}  // namespace brain::core
