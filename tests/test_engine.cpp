#include <cassert>
#include <memory>
#include <string>

#include "brain/communication/DialogBrain.hpp"
#include "brain/core/BrainRegion.hpp"
#include "brain/core/Connectome.hpp"
#include "brain/core/SimulationEngine.hpp"
#include "brain/core/Synapse.hpp"

int main() {
  using brain::core::BrainRegion;
  using brain::core::Connectome;
  using brain::core::HebbianRule;
  using brain::core::SimulationEngine;
  using brain::core::Synapse;

  Connectome connectome;
  auto region = std::make_unique<BrainRegion>("sensory", 4, std::make_unique<HebbianRule>(0.01F));
  region->AddSynapse(Synapse{0, 1, 0.5F, 1});
  region->Stimulate(0, 2.0F);
  region->Stimulate(1, 2.0F);
  connectome.AddRegion(std::move(region));

  SimulationEngine engine(std::move(connectome));
  engine.Tick(0.1F);

  auto* sensory = engine.MutableConnectome().FindRegion("sensory");
  assert(sensory != nullptr);
  assert(sensory->Neurons().at(0).DidSpike());

  const float updated_weight = sensory->Synapses().at(0).weight;
  assert(updated_weight > 0.5F);

  bool threw_negative_delay = false;
  try {
    sensory->AddSynapse(Synapse{1, 2, 0.3F, -1});
  } catch (...) {
    threw_negative_delay = true;
  }
  assert(threw_negative_delay);

  bool threw_null = false;
  try {
    std::unique_ptr<BrainRegion> null_region;
    engine.MutableConnectome().AddRegion(std::move(null_region));
  } catch (...) {
    threw_null = true;
  }
  assert(threw_null);

  brain::communication::DialogBrain brain;
  const std::size_t before_memory = brain.MemorySize();
  assert(before_memory >= 2);

  const bool learned = brain.Teach("hi there => hello human");
  assert(learned);

  const std::string reply = brain.Reply("hi there", "focus");
  assert(reply == "hello human");

  const std::string fallback = brain.Reply("completely new phrase", "explore");
  assert(!fallback.empty());
  assert(brain.MemorySize() == before_memory + 1);

  return 0;
}
