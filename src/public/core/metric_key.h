#ifndef METALHEART_TELEMETRY_METRIC_KEY_H
#define METALHEART_TELEMETRY_METRIC_KEY_H

#include <string>
#include <unordered_map>

namespace telemetry {

/// @brief Every metric is uniquely identified by its metric name and optional
/// key-value pairs called labels.
struct MetricKey {
  std::string                                  name;
  std::unordered_map<std::string, std::string> labels;
  std::string                                  description;

  bool operator==(const MetricKey& other) const {
    return name == other.name            //
               ? labels == other.labels  //
               : false;
  };
};

}  // namespace telemetry

namespace std {
template <>
struct hash<telemetry::MetricKey> {
  size_t operator()(const telemetry::MetricKey& key) const {
    return hash<string>()(key.name);
  }
};
}  // namespace std

#endif  // METALHEART_TELEMETRY_METRIC_KEY_H