#include <algorithm>

#include "brain/cognitive/Agent.hpp"

namespace brain::cognitive {

Agent::Agent(AgentProfile profile, brain::core::SimulationEngine engine)
    : profile_(std::move(profile)), engine_(std::move(engine)) {}

std::string Agent::Step(const std::vector<float>& sensory_input, const float dt) {
  brain::core::Connectome& connectome = engine_.MutableConnectome();
  if (brain::core::BrainRegion* sensory = connectome.FindRegion("sensory")) {
    const std::size_t cap = std::min(sensory_input.size(), sensory->Neurons().size());
    for (std::size_t i = 0; i < cap; ++i) {
      sensory->Stimulate(i, sensory_input[i]);
    }
  }

  engine_.Tick(dt);
  return planner_.SelectAction(sensory_input);
}

const AgentProfile& Agent::Profile() const {
  return profile_;
}

}  // namespace brain::cognitive
