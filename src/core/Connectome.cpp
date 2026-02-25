#include "brain/core/Connectome.hpp"

#include <stdexcept>

namespace brain::core {

std::size_t Connectome::AddRegion(std::unique_ptr<BrainRegion> region) {
  const std::string name = region->Name();
  if (index_by_name_.contains(name)) {
    throw std::invalid_argument("Region already exists: " + name);
  }

  const std::size_t index = regions_.size();
  index_by_name_[name] = index;
  regions_.push_back(std::move(region));
  return index;
}

BrainRegion* Connectome::FindRegion(const std::string& name) {
  const auto it = index_by_name_.find(name);
  if (it == index_by_name_.end()) {
    return nullptr;
  }
  return regions_[it->second].get();
}

const std::vector<std::unique_ptr<BrainRegion>>& Connectome::Regions() const {
  return regions_;
}

}  // namespace brain::core
