#pragma once

#include <string>
#include <vector>

namespace brain::cognitive {

class Planner {
 public:
  [[nodiscard]] std::string SelectAction(const std::vector<float>& percept_vector) const;
};

}  // namespace brain::cognitive
