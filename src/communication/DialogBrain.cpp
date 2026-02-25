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

std::string DialogBrain::Reply(const std::string& user_text) {
  const std::string trimmed = Trim(user_text);
  if (trimmed.empty()) {
    return "Please share a message so I can learn from it.";
  }

  for (const std::string& token : Tokenize(trimmed)) {
    ++token_frequency_[token];
  }

  if (const std::optional<std::size_t> match = FindBestMatchIndex(trimmed)) {
    DialogueExample& learned = memory_.at(*match);
    ++learned.uses;
    return learned.assistant;
  }

  const std::string generated = GenerateComposedReply(trimmed);
  memory_.push_back({trimmed, generated, 1});
  return generated;
}

bool DialogBrain::Teach(const std::string& instruction) {
  const std::string marker = "=>";
  const std::size_t split = instruction.find(marker);
  if (split == std::string::npos) {
    return false;
  }

  const std::string user_text = Trim(instruction.substr(0, split));
  const std::string assistant_text = Trim(instruction.substr(split + marker.size()));
  if (user_text.empty() || assistant_text.empty()) {
    return false;
  }

  memory_.push_back({user_text, assistant_text, 0});
  for (const std::string& token : Tokenize(user_text)) {
    ++token_frequency_[token];
  }
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

std::string DialogBrain::GenerateComposedReply(const std::string& user_text) const {
  const std::vector<std::string> tokens = Tokenize(user_text);
  std::ostringstream out;
  out << "I heard:";

  if (tokens.empty()) {
    out << " (no words).";
    return out.str();
  }

  std::size_t count = 0;
  for (const std::string& token : tokens) {
    if (count >= 8) {
      break;
    }
    out << ' ' << token;
    ++count;
  }
  out << ".";

  auto best = std::max_element(token_frequency_.begin(), token_frequency_.end(), [](const auto& left, const auto& right) {
    return left.second < right.second;
  });

  if (best != token_frequency_.end()) {
    out << " Most frequent concept so far: " << best->first << ".";
  }

  out << " You can refine my answer with: teach: your text => desired response";
  return out.str();
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

}  // namespace brain::communication
