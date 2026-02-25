#include "brain/core/BrainRegion.hpp"

#include <algorithm>
#include <stdexcept>

namespace brain::core {

void HebbianRule::Update(Synapse& synapse, const bool pre_spike, const bool post_spike, const float dt) {
  if (pre_spike && post_spike) {
    synapse.weight += learning_rate_ * dt;
  } else if (pre_spike != post_spike) {
    synapse.weight -= learning_rate_ * dt * 0.1F;
  }
  synapse.weight = std::clamp(synapse.weight, -3.0F, 3.0F);
}

BrainRegion::BrainRegion(std::string name, const std::size_t neuron_count, std::unique_ptr<LearningRule> learning_rule)
    : name_(std::move(name)), neurons_(neuron_count), learning_rule_(std::move(learning_rule)) {
  if (!learning_rule_) {
    throw std::invalid_argument("learning_rule must not be null");
  }
}

void BrainRegion::Stimulate(const std::size_t neuron_index, const float input_current) {
  if (neuron_index >= neurons_.size()) {
    throw std::out_of_range("neuron_index out of range");
  }
  neurons_[neuron_index].Integrate(input_current);
}

void BrainRegion::Step(const float dt) {
  for (Neuron& neuron : neurons_) {
    neuron.Advance();
  }

  for (Synapse& synapse : synapses_) {
    const bool pre_spike = neurons_.at(synapse.pre_index).DidSpike();
    const bool post_spike = neurons_.at(synapse.post_index).DidSpike();

    if (pre_spike) {
      neurons_.at(synapse.post_index).Integrate(synapse.weight);
    }

    learning_rule_->Update(synapse, pre_spike, post_spike, dt);
  }
}

void BrainRegion::AddSynapse(const Synapse& synapse) {
  if (synapse.pre_index >= neurons_.size() || synapse.post_index >= neurons_.size()) {
    throw std::out_of_range("synapse index out of range");
  }
  synapses_.push_back(synapse);
}

const std::string& BrainRegion::Name() const {
  return name_;
}

const std::vector<Neuron>& BrainRegion::Neurons() const {
  return neurons_;
}

std::vector<Neuron>& BrainRegion::MutableNeurons() {
  return neurons_;
}

const std::vector<Synapse>& BrainRegion::Synapses() const {
  return synapses_;
}

}  // namespace brain::core
