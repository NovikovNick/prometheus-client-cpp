#include "gauge.h"

#include <cmath>
#include <format>

namespace telemetry {
Gauge::Gauge(const MetricKey& key)
    : Metric(Type::Gauge, key),  //
      value_(0.0),
      metric_description_(""){};

void Gauge::measure(double value) { value_.store(value); };

void Gauge::collect(std::string& out) {
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
