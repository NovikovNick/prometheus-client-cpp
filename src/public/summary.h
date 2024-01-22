#ifndef METALHEART_TELEMETRY_SUMMARY_H
#define METALHEART_TELEMETRY_SUMMARY_H

#include <chrono>
#include <mutex>
#include <queue>
#include <set>
#include <vector>

#include "types.h"

namespace telemetry {

/// @brief Similar to a histogram, a summary samples observations (usually
/// things like request durations and response sizes). While it also provides a
/// total count of observations and a sum of all observed values, it calculates
/// configurable quantiles over a sliding time window.
///
/// https://prometheus.io/docs/concepts/metric_types/#summary
///
class Summary final : public Metric {
  using Clock     = std::chrono::steady_clock;
  using Timepoint = Clock::time_point;

  std::mutex                mutex_;
  std::multiset<double>     values_;
  std::chrono::milliseconds sliding_time_window_;
  std::queue<std::pair<Timepoint, std::set<double>::iterator>> refs_;
  std::vector<double>                                          quantiles_;

  Summary(const MetricKey           &key,
          std::chrono::milliseconds  sliding_time_window,
          const std::vector<double> &quantiles);

 public:
  void measure(double value);

  virtual void collect(std::string &out) override;

  friend MetricRegistry;
};

/// @brief builder with access to the metrics registry
///
class SummaryBuilder : public MetricBuilder<Summary, SummaryBuilder> {
  std::chrono::milliseconds sliding_time_window_;
  std::vector<double>       quantiles_;

 public:
  SummaryBuilder &sliding_time_window(std::chrono::milliseconds val) {
    sliding_time_window_ = val;
    return *this;
  }

  template <typename... Args>
  SummaryBuilder &quantiles(Args &&...args) {
    (quantiles_.push_back(args), ...);
    return *this;
  }

  virtual Summary &get() override {
    return build(sliding_time_window_, quantiles_);
  };

  virtual void measure(double value) override { get().measure(value); };
};

}  // namespace telemetry

#endif  // METALHEART_TELEMETRY_SUMMARY_H
