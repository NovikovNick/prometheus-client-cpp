#include "gauge.h"

#include <cmath>
#include <format>

namespace telemetry {
Gauge::Gauge(const MetricKey& key) : Metric(key), value_(0.0){};

void Gauge::measure(double value) { value_.store(value); };

void Gauge::collect(std::string& out) {
  out += std::format("# HELP {} {}\n", key_.name, key_.description);
  out += std::format("# TYPE {} gauge\n", key_.name);
  out += std::format("{}", key_.name);
  collectLabels(out);
  out += std::format(" {}\n", value_.load());
};
}  // namespace telemetry
