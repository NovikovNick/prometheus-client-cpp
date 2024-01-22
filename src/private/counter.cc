#include "counter.h"

#include <cassert>
#include <cmath>
#include <format>

namespace telemetry {
Counter::Counter(const MetricKey& key) : Metric(key), value_(0){};

uint64_t Counter::value() const { return value_.load(); }

void Counter::measure(int value) {
  assert(value >= 0);
  value_.fetch_add(value);
};

void Counter::collect(std::string& out) {
  out += std::format("# HELP {} {}\n", key_.name, key_.description);
  out += std::format("# TYPE {} counter\n", key_.name);
  out += std::format("{}", key_.name);
  collectLabels(out);
  out += std::format(" {}\n", value_.load());
};
}  // namespace telemetry
