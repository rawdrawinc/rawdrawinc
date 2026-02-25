#include "brain/communication/AuditTrail.hpp"

#include <fstream>

namespace brain::communication {

void AuditTrail::Record(const AuditEvent& event) {
  events_.push_back(event);
}

bool AuditTrail::FlushToJsonl(const std::string& path) const {
  std::ofstream out(path, std::ios::out | std::ios::app);
  if (!out) {
    return false;
  }

  for (const AuditEvent& event : events_) {
    out << "{\"timestamp_utc\":\"" << event.timestamp_utc << "\","
        << "\"user_id\":\"" << event.user_id << "\","
        << "\"action\":\"" << event.action << "\","
        << "\"outcome\":\"" << event.outcome << "\"}\n";
  }
  return true;
}

}  // namespace brain::communication
