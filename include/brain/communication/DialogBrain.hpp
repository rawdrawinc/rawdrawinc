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

  [[nodiscard]] std::string Reply(const std::string& user_text, const std::string& cognitive_action);
  bool Teach(const std::string& instruction);

  [[nodiscard]] std::size_t MemorySize() const;

 private:
  static constexpr std::size_t kMaxMemoryExamples = 2048;
  static constexpr std::size_t kMaxTokenFrequencyEntries = 4096;
  static constexpr std::size_t kMaxInputLength = 512;
  static constexpr std::size_t kMaxStoredUtteranceLength = 256;
  static constexpr std::size_t kMaxStoredResponseLength = 256;

  std::vector<DialogueExample> memory_;
  std::unordered_map<std::string, std::size_t> token_frequency_;

  static std::vector<std::string> Tokenize(const std::string& text);
  [[nodiscard]] std::optional<std::size_t> FindBestMatchIndex(const std::string& user_text) const;
  [[nodiscard]] std::string GenerateComposedReply(const std::string& cognitive_action) const;
  static std::string Trim(const std::string& value);
  [[nodiscard]] static std::string Truncate(const std::string& input, std::size_t max_len);
  void BoundedUpdateTokenFrequency(const std::vector<std::string>& tokens);
  void BoundedAppendMemory(DialogueExample example);
};

}  // namespace brain::communication
