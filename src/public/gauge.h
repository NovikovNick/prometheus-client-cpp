#ifndef METALHEART_TELEMETRY_GAUGE_H
#define METALHEART_TELEMETRY_GAUGE_H

#include <atomic>
#include <string>

#include "types.h"

namespace telemetry {

/// @brief Single numerical value that can arbitrarily go up and down.
///
/// https://prometheus.io/docs/concepts/metric_types/#gauge
///
class Gauge final : public Metric {
  std::atomic<double> value_;
  std::string         metric_description_;

  Gauge(const MetricKey& key);

 public:
  void measure(double value);

  virtual void collect(std::string& out) override;

  friend MetricRegistry;
};

/// @brief builder with access to the metrics registry
///
class GaugeBuilder : public MetricBuilder<Gauge, GaugeBuilder> {
 public:
  virtual Gauge& get() override { return build(Metric::Type::Gauge); };
  virtual void   measure(double value) override { get().measure(value); }
};

}  // namespace telemetry

#endif  // METALHEART_TELEMETRY_GAUGE_H
