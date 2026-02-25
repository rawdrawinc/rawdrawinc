#pragma once

#include <cstdint>

namespace brain::core {

struct NeuronState {
  float membrane_potential{0.0F};
  bool spiked{false};
};

class Neuron {
 public:
  explicit Neuron(float threshold = 1.0F, float leak = 0.95F);

  void Integrate(float input_current);
  void Advance();

  [[nodiscard]] bool DidSpike() const;
  [[nodiscard]] float Potential() const;

 private:
  float threshold_;
  float leak_;
  NeuronState state_;
};

}  // namespace brain::core
