#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "brain/core/BrainRegion.hpp"

namespace brain::core {

class Connectome {
 public:
  std::size_t AddRegion(std::unique_ptr<BrainRegion> region);
  BrainRegion* FindRegion(const std::string& name);

  [[nodiscard]] const std::vector<std::unique_ptr<BrainRegion>>& Regions() const;

 private:
  std::vector<std::unique_ptr<BrainRegion>> regions_;
  std::unordered_map<std::string, std::size_t> index_by_name_;
};

}  // namespace brain::core
