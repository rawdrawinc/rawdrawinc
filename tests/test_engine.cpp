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

  brain::communication::DialogBrain brain;
  assert(brain.MemorySize() >= 2);

  const bool learned = brain.Teach("hi there => hello human");
  assert(learned);

  const std::string reply = brain.Reply("hi there");
  assert(reply == "hello human");

  const std::string fallback = brain.Reply("completely new phrase");
  assert(!fallback.empty());

  return 0;
}
