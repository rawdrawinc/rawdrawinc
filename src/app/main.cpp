#include <algorithm>
#include <chrono>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <ctime>

#include "brain/cognitive/Agent.hpp"
#include "brain/communication/AuditTrail.hpp"
#include "brain/communication/DialogBrain.hpp"
#include "brain/core/BrainRegion.hpp"
#include "brain/core/Connectome.hpp"
#include "brain/core/SimulationEngine.hpp"

namespace {

std::string UtcTimestampNow() {
  const auto now = std::chrono::system_clock::now();
  const std::time_t time_now = std::chrono::system_clock::to_time_t(now);
  std::tm time_struct{};
#if defined(_WIN32)
  gmtime_s(&time_struct, &time_now);
#else
  gmtime_r(&time_now, &time_struct);
#endif
  char buffer[32]{};
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &time_struct);
  return buffer;
}

std::string SanitizeForTerminal(const std::string& text) {
  std::string sanitized;
  sanitized.reserve(text.size());
  for (const unsigned char ch : text) {
    if (ch == '\t' || ch == ' ') {
      sanitized.push_back(static_cast<char>(ch));
      continue;
    }
    if (ch >= 32 && ch <= 126) {
      sanitized.push_back(static_cast<char>(ch));
    }
  }
  return sanitized;
}

std::vector<float> ConvertTextToSensory(const std::string& input) {
  std::vector<float> sensory(16, 0.0F);
  for (std::size_t i = 0; i < input.size(); ++i) {
    sensory[i % sensory.size()] += static_cast<float>(static_cast<unsigned char>(input[i])) / 255.0F;
  }
  for (float& value : sensory) {
    value = std::min(value, 1.0F);
  }
  return sensory;
}

}  // namespace

int main() {
  using brain::core::BrainRegion;
  using brain::core::Connectome;
  using brain::core::HebbianRule;
  using brain::core::SimulationEngine;

  try {
    Connectome connectome;
    auto sensory = std::make_unique<BrainRegion>("sensory", 64, std::make_unique<HebbianRule>(0.001F));
    connectome.AddRegion(std::move(sensory));
    SimulationEngine engine(std::move(connectome));

    brain::cognitive::AgentProfile profile;
    profile.alias = "CLIUserModel";
    brain::cognitive::Agent agent(profile, std::move(engine));

    brain::communication::DialogBrain dialog;
    brain::communication::AuditTrail audit_trail;

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
        const bool ok = dialog.Teach(instruction);
        audit_trail.Record({UtcTimestampNow(), "local-cli", "teach", ok ? "success" : "invalid_format"});

        if (ok) {
          std::cout << "Learning stored.\n";
        } else {
          std::cout << "Invalid teach format. Use: teach: your input => desired response\n";
        }
        continue;
      }

      const std::vector<float> sensory_input = ConvertTextToSensory(line);
      const std::string action = agent.Step(sensory_input, 0.05F);
      const std::string reply = dialog.Reply(line, action);
      std::cout << SanitizeForTerminal(reply) << "\n";
    }

    if (!audit_trail.FlushToJsonl("audit.log.jsonl")) {
      std::cerr << "Warning: audit log could not be persisted.\n";
    }

    return 0;
  } catch (const std::exception&) {
    std::cerr << "A runtime error occurred. Please restart the application.\n";
    return 1;
  } catch (...) {
    std::cerr << "An unexpected error occurred. Please restart the application.\n";
    return 1;
  }
}
