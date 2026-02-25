#include "brain/communication/DialogBrain.hpp"

#include <algorithm>
#include <cctype>
#include <set>
#include <sstream>

namespace brain::communication {

DialogBrain::DialogBrain() {
  memory_.push_back({"hello", "Hello. I am listening.", 0});
  memory_.push_back({"who are you", "I am a digital brain simulation process.", 0});
}

std::string DialogBrain::Reply(const std::string& user_text, const std::string& cognitive_action) {
  const std::string trimmed = Truncate(Trim(user_text), kMaxInputLength);
  if (trimmed.empty()) {
    return "Please share a message so I can learn from it.";
  }

  if (const std::optional<std::size_t> match = FindBestMatchIndex(trimmed)) {
    DialogueExample& learned = memory_.at(*match);
    ++learned.uses;
    return learned.assistant;
  }

  return GenerateComposedReply(cognitive_action);
}

bool DialogBrain::Teach(const std::string& instruction) {
  const std::string bounded = Truncate(instruction, kMaxInputLength);
  const std::string marker = "=>";
  const std::size_t split = bounded.find(marker);
  if (split == std::string::npos) {
    return false;
  }

  const std::string user_text = Truncate(Trim(bounded.substr(0, split)), kMaxStoredUtteranceLength);
  const std::string assistant_text = Truncate(Trim(bounded.substr(split + marker.size())), kMaxStoredResponseLength);
  if (user_text.empty() || assistant_text.empty()) {
    return false;
  }

  for (DialogueExample& example : memory_) {
    if (Trim(example.user) == user_text) {
      example.assistant = assistant_text;
      example.uses = 0;
      BoundedUpdateTokenFrequency(Tokenize(user_text));
      return true;
    }
  }

  BoundedAppendMemory({user_text, assistant_text, 0});
  BoundedUpdateTokenFrequency(Tokenize(user_text));
  return true;
}

std::size_t DialogBrain::MemorySize() const {
  return memory_.size();
}

std::vector<std::string> DialogBrain::Tokenize(const std::string& text) {
  std::string normalized;
  normalized.reserve(text.size());

  for (const char ch : text) {
    if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
      normalized.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    } else {
      normalized.push_back(' ');
    }
  }

  std::istringstream stream(normalized);
  std::vector<std::string> tokens;
  std::string token;
  while (stream >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

std::optional<std::size_t> DialogBrain::FindBestMatchIndex(const std::string& user_text) const {
  const std::vector<std::string> input_tokens = Tokenize(user_text);
  if (input_tokens.empty()) {
    return std::nullopt;
  }

  const std::set<std::string> input_set(input_tokens.begin(), input_tokens.end());
  double best_score = 0.0;
  std::optional<std::size_t> best_index;

  for (std::size_t i = 0; i < memory_.size(); ++i) {
    const std::vector<std::string> example_tokens = Tokenize(memory_.at(i).user);
    const std::set<std::string> example_set(example_tokens.begin(), example_tokens.end());

    std::size_t overlap = 0;
    for (const std::string& token : input_set) {
      if (example_set.contains(token)) {
        ++overlap;
      }
    }

    const std::size_t union_size = input_set.size() + example_set.size() - overlap;
    if (union_size == 0) {
      continue;
    }

    const double score = static_cast<double>(overlap) / static_cast<double>(union_size);
    if (score > best_score) {
      best_score = score;
      best_index = i;
    }
  }

  if (best_score < 0.25) {
    return std::nullopt;
  }
  return best_index;
}

std::string DialogBrain::GenerateComposedReply(const std::string& cognitive_action) const {
  if (cognitive_action == "focus") {
    return "I am focusing on your message. Teach me with: teach: input => response";
  }
  if (cognitive_action == "explore") {
    return "I am exploring options. Teach me with: teach: input => response";
  }
  return "I am listening. Teach me with: teach: input => response";
}

std::string DialogBrain::Trim(const std::string& value) {
  const auto first = std::find_if_not(value.begin(), value.end(), [](const char ch) {
    return std::isspace(static_cast<unsigned char>(ch)) != 0;
  });
  if (first == value.end()) {
    return {};
  }

  const auto last = std::find_if_not(value.rbegin(), value.rend(), [](const char ch) {
    return std::isspace(static_cast<unsigned char>(ch)) != 0;
  }).base();

  return std::string(first, last);
}

std::string DialogBrain::Truncate(const std::string& input, const std::size_t max_len) {
  if (input.size() <= max_len) {
    return input;
  }
  return input.substr(0, max_len);
}

void DialogBrain::BoundedUpdateTokenFrequency(const std::vector<std::string>& tokens) {
  for (const std::string& token : tokens) {
    if (token_frequency_.contains(token)) {
      ++token_frequency_[token];
      continue;
    }

    if (token_frequency_.size() >= kMaxTokenFrequencyEntries) {
      continue;
    }
    token_frequency_[token] = 1;
  }
}

void DialogBrain::BoundedAppendMemory(DialogueExample example) {
  if (memory_.size() >= kMaxMemoryExamples) {
    memory_.erase(memory_.begin());
  }
  memory_.push_back(std::move(example));
}

}  // namespace brain::communication
