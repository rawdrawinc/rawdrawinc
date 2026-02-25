#include <iostream>
#include <memory>
#include <string>

#include "brain/communication/DialogBrain.hpp"
#include "brain/core/BrainRegion.hpp"
#include "brain/core/Connectome.hpp"
#include "brain/core/SimulationEngine.hpp"

int main() {
  using brain::core::BrainRegion;
  using brain::core::Connectome;
  using brain::core::HebbianRule;
  using brain::core::SimulationEngine;

  Connectome connectome;
  auto sensory = std::make_unique<BrainRegion>("sensory", 64, std::make_unique<HebbianRule>(0.001F));
  connectome.AddRegion(std::move(sensory));
  SimulationEngine engine(std::move(connectome));

  brain::communication::DialogBrain dialog;

  std::cout << "Digital Brain interface ready.\n";
  std::cout << "Type messages to communicate.\n";
  std::cout << "Commands: /quit, /help, /memory\n";
  std::cout << "Training format: teach: your input => desired response\n\n";

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "/quit") {
      std::cout << "Session ended.\n";
      break;
    }

    if (line == "/help") {
      std::cout << "Use plain text to converse. Use teach: input => output to train me directly.\n";
      continue;
    }

    if (line == "/memory") {
      std::cout << "Stored dialogue patterns: " << dialog.MemorySize() << "\n";
      continue;
    }

    if (line.rfind("teach:", 0) == 0) {
      const std::string instruction = line.substr(6);
      if (dialog.Teach(instruction)) {
        std::cout << "Learning stored.\n";
      } else {
        std::cout << "Invalid teach format. Use: teach: your input => desired response\n";
      }
      continue;
    }

    engine.Tick(0.05F);
    std::cout << dialog.Reply(line) << "\n";
  }

  return 0;
}
