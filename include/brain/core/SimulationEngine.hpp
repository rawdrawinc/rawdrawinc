#pragma once

#include <cstddef>

#include "brain/core/Connectome.hpp"

namespace brain::core {

class SimulationEngine {
 public:
  explicit SimulationEngine(Connectome connectome);

  void Tick(float dt);
  void Run(std::size_t steps, float dt);

  [[nodiscard]] std::size_t TickCount() const;
  [[nodiscard]] Connectome& MutableConnectome();

 private:
  Connectome connectome_;
  std::size_t tick_count_{0};
};

}  // namespace brain::core
