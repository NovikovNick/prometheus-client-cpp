#include "core/metric.h"

#include <format>

namespace telemetry {

Metric::Metric(Type type, const MetricKey& key) : key_(key), type_(type) {}

std::string Metric::labelsToString(
    std::unordered_map<std::string, std::string>&& addition_labels) const {
  std::string out;
  if (!key_.labels.empty() || !addition_labels.empty()) {
    for (auto [tag, val] : key_.labels) {
      addition_labels[tag] = val;
    }

    out += '{';
    for (auto [tag, val] : addition_labels) {
      out += std::format("{}=\"{}\",", tag, val);
    }
    out[out.size() - 1] = '}';
  }

  return out;
}

}  // namespace telemetry
