#pragma once

#include <string>
#include <vector>

namespace brain::communication {

struct AuditEvent {
  std::string timestamp_utc;
  std::string user_id;
  std::string action;
  std::string outcome;
};

class AuditTrail {
 public:
  void Record(const AuditEvent& event);
  bool FlushToJsonl(const std::string& path) const;

 private:
  std::vector<AuditEvent> events_;
};

}  // namespace brain::communication
