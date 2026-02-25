#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace brain::communication {

struct DialogueExample {
  std::string user;
  std::string assistant;
  std::size_t uses{0};
};

class DialogBrain {
 public:
  DialogBrain();

  [[nodiscard]] std::string Reply(const std::string& user_text);
  bool Teach(const std::string& instruction);

  [[nodiscard]] std::size_t MemorySize() const;

 private:
  std::vector<DialogueExample> memory_;
  std::unordered_map<std::string, std::size_t> token_frequency_;

  static std::vector<std::string> Tokenize(const std::string& text);
  [[nodiscard]] std::optional<std::size_t> FindBestMatchIndex(const std::string& user_text) const;
  [[nodiscard]] std::string GenerateComposedReply(const std::string& user_text) const;
  static std::string Trim(const std::string& value);
};

}  // namespace brain::communication
