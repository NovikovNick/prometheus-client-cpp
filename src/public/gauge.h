#ifndef METALHEART_TELEMETRY_GAUGE_H
#define METALHEART_TELEMETRY_GAUGE_H

#include <atomic>
#include <string>

#include "types.h"

namespace telemetry {

class Gauge final : public Metric {
  std::atomic<double> value_;

 public:
  Gauge(const MetricKey& key) : Metric(key), value_(0.0){};

  virtual void measure(double value) override;

  virtual void collect(std::string& out) override;
};

class GaugeBuilder : public MetricBuilder<Gauge, GaugeBuilder> {
 public:
  virtual Gauge& get() override { return build(); };
  virtual void   measure(double value) override { get().measure(value); }
};

}  // namespace telemetry

#endif  // METALHEART_TELEMETRY_GAUGE_H
