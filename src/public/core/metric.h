#ifndef METALHEART_TELEMETRY_METRIC_H
#define METALHEART_TELEMETRY_METRIC_H

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
  Metric(const MetricKey& key);

  virtual void collect(std::string& out) = 0;
  virtual ~Metric()                      = default;

 protected:
  MetricKey key_;

  void collectLabels(std::string& out) const;
};

};  // namespace telemetry

#endif  // METALHEART_TELEMETRY_METRIC_H