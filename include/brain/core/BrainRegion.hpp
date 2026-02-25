#pragma once

#include <memory>
#include <string>
#include <vector>

#include "brain/core/LearningRule.hpp"
#include "brain/core/Neuron.hpp"
#include "brain/core/Synapse.hpp"

namespace brain::core {

class BrainRegion {
 public:
  BrainRegion(std::string name, std::size_t neuron_count, std::unique_ptr<LearningRule> learning_rule);

  void Stimulate(std::size_t neuron_index, float input_current);
  void Step(float dt);

  void AddSynapse(const Synapse& synapse);

  [[nodiscard]] const std::string& Name() const;
  [[nodiscard]] const std::vector<Neuron>& Neurons() const;
  [[nodiscard]] std::vector<Neuron>& MutableNeurons();
  [[nodiscard]] const std::vector<Synapse>& Synapses() const;

 private:
  std::string name_;
  std::vector<Neuron> neurons_;
  std::vector<Synapse> synapses_;
  std::unique_ptr<LearningRule> learning_rule_;
};

}  // namespace brain::core
