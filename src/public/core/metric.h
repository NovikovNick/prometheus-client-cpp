#ifndef METALHEART_TELEMETRY_METRIC_H
#define METALHEART_TELEMETRY_METRIC_H

#include <string>
#include <unordered_map>

#include "metric_key.h"

namespace telemetry {

/// @brief Holds metrics data. Nether copyable nor moveable.
///
class Metric {
  Metric(const Metric&)            = delete;
  Metric& operator=(const Metric&) = delete;
  Metric(Metric&&)                 = delete;
  Metric& operator=(Metric&&)      = delete;

 public:
  enum class Type { Counter, Gauge, Histogram, Summary };

  Metric(Type type, const MetricKey& key);
  virtual void collect(std::string& out) = 0;
  virtual ~Metric()                      = default;

  Type type() const { return type_; };

 protected:
  MetricKey key_;
  Type      type_;

  std::string labelsToString(
      std::unordered_map<std::string, std::string>&& addition_labels) const;
};

};  // namespace telemetry

#endif  // METALHEART_TELEMETRY_METRIC_H