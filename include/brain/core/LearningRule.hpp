#pragma once

#include "brain/core/Synapse.hpp"

namespace brain::core {

class LearningRule {
 public:
  virtual ~LearningRule() = default;
  virtual void Update(Synapse& synapse, bool pre_spike, bool post_spike, float dt) = 0;
};

class HebbianRule final : public LearningRule {
 public:
  explicit HebbianRule(float learning_rate = 0.001F) : learning_rate_(learning_rate) {}
  void Update(Synapse& synapse, bool pre_spike, bool post_spike, float dt) override;

 private:
  float learning_rate_;
};

}  // namespace brain::core
