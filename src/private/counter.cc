#include "counter.h"

#include <cassert>
#include <cmath>
#include <format>
#include <string_view>

namespace telemetry {
Counter::Counter(const MetricKey& key)
    : Metric(Type::Counter, key),  //
      value_(0),
      metric_description_(""){};

uint64_t Counter::value() const { return value_.load(); }

void Counter::measure(int value) {
  assert(value >= 0);
  value_.fetch_add(value);
};

void Counter::collect(std::string& out) {
  if (metric_description_.empty()) {
    metric_description_ = std::format(
        "# HELP {} {}\n"
        "# TYPE {} counter\n"
        "{}{} ",
        key_.name,
        key_.description,
        key_.name,
        key_.name,
        labelsToString({}));
  }
  out += metric_description_;
  out += std::to_string(value_.load());
  out += '\n';
};
}  // namespace telemetry
