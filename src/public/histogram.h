#ifndef METALHEART_TELEMETRY_HISTOGRAM_H
#define METALHEART_TELEMETRY_HISTOGRAM_H

#include <atomic>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "types.h"

namespace telemetry {

/// @brief A histogram samples observations (usually things like request
/// durations or response sizes) and counts them in configurable buckets. It
/// also provides a sum of all observed values.
///
/// https://prometheus.io/docs/concepts/metric_types/#histogram
///
class Histogram final : public Metric {
  std::mutex                mutex_;
  double                    sum;
  std::map<double, int64_t> buckets_;

  Histogram(const MetricKey& key, const std::vector<double>& buckets);

 public:
  void measure(double value);

  virtual void collect(std::string& out) override;

  friend MetricRegistry;
};

/// @brief builder with access to the metrics registry
///
class HistogramBuilder : public MetricBuilder<Histogram, HistogramBuilder> {
  std::vector<double> buckets_;

 public:
  template <typename... Args>
  HistogramBuilder& buckets(Args&&... args) {
    (buckets_.push_back(args), ...);
    return *this;
  }

  virtual Histogram& get() override { return build(buckets_); };

  virtual void measure(double value) override { get().measure(value); }
};

}  // namespace telemetry

#endif  // METALHEART_TELEMETRY_HISTOGRAM_H
