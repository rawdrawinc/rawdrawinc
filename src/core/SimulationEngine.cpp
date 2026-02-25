#include "brain/core/SimulationEngine.hpp"

namespace brain::core {

SimulationEngine::SimulationEngine(Connectome connectome) : connectome_(std::move(connectome)) {}

void SimulationEngine::Tick(const float dt) {
  for (const auto& region : connectome_.Regions()) {
    region->Step(dt);
  }
  ++tick_count_;
}

void SimulationEngine::Run(const std::size_t steps, const float dt) {
  for (std::size_t i = 0; i < steps; ++i) {
    Tick(dt);
  }
}

std::size_t SimulationEngine::TickCount() const {
  return tick_count_;
}

Connectome& SimulationEngine::MutableConnectome() {
  return connectome_;
}

}  // namespace brain::core
