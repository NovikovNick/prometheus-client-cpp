#ifndef METALHEART_TELEMETRY_COUNTER_H
#define METALHEART_TELEMETRY_COUNTER_H

#include <atomic>
#include <string>

#include "types.h"

namespace telemetry {

class Counter final : public Metric {
  std::atomic<uint64_t> value_;

 public:
  Counter(const MetricKey& key) : Metric(key), value_(0){};

  void         increment();
  int          value() const;
  virtual void measure(double value) override;

  virtual void collect(std::string& out) override;
};

class CounterBuilder : public MetricBuilder<Counter, CounterBuilder> {
 public:
  virtual Counter& get() override { return build(); };
  virtual void     measure(double value) override { get().measure(value); }
};

}  // namespace telemetry

#endif  // METALHEART_TELEMETRY_COUNTER_H
