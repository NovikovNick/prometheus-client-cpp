#ifndef METALHEART_TELEMETRY_COUNTER_H
#define METALHEART_TELEMETRY_COUNTER_H

#include <atomic>
#include <string>

#include "types.h"

namespace telemetry {

class CounterBuilder;

/// @brief What could be more obvious than a counter? :)
/// Can be only incremented
///
/// https://prometheus.io/docs/concepts/metric_types/#counter
///
class Counter final : public Metric {
  std::atomic<uint64_t> value_;
  std::string           metric_description_;

  Counter(const MetricKey& key);

 public:
  /// @brief simple getter
  /// @return counter value
  uint64_t value() const;

  /// @brief increases the counter value by a specific amount
  /// @param value strict positive amount
  void measure(int amount);

  virtual void collect(std::string& out) override;

  friend MetricRegistry;
};

/// @brief builder with access to the metrics registry
///
class CounterBuilder : public MetricBuilder<Counter, CounterBuilder> {
 public:
  virtual Counter& get() override { return build(Metric::Type::Counter); };
  virtual void     measure(double value) override { get().measure(value); }
};

}  // namespace telemetry

#endif  // METALHEART_TELEMETRY_COUNTER_H
