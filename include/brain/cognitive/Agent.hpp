#pragma once

#include <string>
#include <vector>

#include "brain/cognitive/Planner.hpp"
#include "brain/core/SimulationEngine.hpp"

namespace brain::cognitive {

struct AgentProfile {
  std::string alias{"DefaultAgent"};
  int age_years{16};
  std::string gender{"unspecified"};
  std::string ethnicity{"unspecified"};
  std::string socioeconomic_background{"unspecified"};
};

class Agent {
 public:
  Agent(AgentProfile profile, brain::core::SimulationEngine engine);

  std::string Step(const std::vector<float>& sensory_input, float dt);
  [[nodiscard]] const AgentProfile& Profile() const;

 private:
  AgentProfile profile_;
  Planner planner_;
  brain::core::SimulationEngine engine_;
};

}  // namespace brain::cognitive
