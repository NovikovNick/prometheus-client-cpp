#include "core/metric.h"

#include <format>

namespace telemetry {

Metric::Metric(const MetricKey& key) : key_(key) {}

void Metric::collectLabels(std::string& out) const {
  if (!key_.labels.empty()) {
    out += '{';
    for (auto [tag, val] : key_.labels) {
      out += std::format("{}=\"{}\",", tag, val);
    }
    out[out.size() - 1] = '}';
  }
}

}  // namespace telemetry
