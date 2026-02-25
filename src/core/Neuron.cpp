#include "brain/core/Neuron.hpp"

namespace brain::core {

Neuron::Neuron(const float threshold, const float leak) : threshold_(threshold), leak_(leak) {}

void Neuron::Integrate(const float input_current) {
  state_.membrane_potential += input_current;
}

void Neuron::Advance() {
  state_.spiked = state_.membrane_potential >= threshold_;
  state_.membrane_potential = state_.spiked ? 0.0F : state_.membrane_potential * leak_;
}

bool Neuron::DidSpike() const {
  return state_.spiked;
}

float Neuron::Potential() const {
  return state_.membrane_potential;
}

}  // namespace brain::core
