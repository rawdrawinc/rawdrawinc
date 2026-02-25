#include "brain/cognitive/Planner.hpp"

#include <algorithm>

namespace brain::cognitive {

std::string Planner::SelectAction(const std::vector<float>& percept_vector) const {
  if (percept_vector.empty()) {
    return "idle";
  }

  const float max_signal = *std::max_element(percept_vector.begin(), percept_vector.end());
  if (max_signal > 0.8F) {
    return "focus";
  }
  if (max_signal > 0.4F) {
    return "explore";
  }
  return "rest";
}

}  // namespace brain::cognitive
