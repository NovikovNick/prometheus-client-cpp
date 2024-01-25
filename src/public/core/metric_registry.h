#ifndef METALHEART_TELEMETRY_METRIC_REGISTRY_H
#define METALHEART_TELEMETRY_METRIC_REGISTRY_H

#include <cassert>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "metric.h"
#include "metric_key.h"

namespace telemetry {

/// @brief Guarantees that metrics are unique. Thread-safe. Singleton
///
class MetricRegistry {
  MetricRegistry()                                 = default;
  MetricRegistry(const MetricRegistry&)            = delete;
  MetricRegistry& operator=(const MetricRegistry&) = delete;

  std::mutex                                             mx_;
  std::unordered_map<MetricKey, std::unique_ptr<Metric>> metrics_;

 public:
  static MetricRegistry& instance() {
    static MetricRegistry inst;
    return inst;
  }

  void forEach(std::function<void(Metric*)> func) {
    std::vector<Metric*> all_metrics;
    {
      std::unique_lock lock(mx_);
      all_metrics.reserve(metrics_.size());
      for (auto& [_, metric] : metrics_) {
        all_metrics.emplace_back(metric.get());
      }
    }

    for (auto metric : all_metrics) {
      func(metric);
    }
  }

  template <typename M, typename... Args>
  M& ensureExist(const Metric::Type type,
                 const MetricKey&   key,
                 Args&&... args) {
    std::unique_lock lock(mx_);

    if (auto it = metrics_.find(key); it != metrics_.end()) {
      Metric& metric = *(it->second.get());
      assert(type == metric.type());
      return static_cast<M&>(metric);
    } else {
      M* metric_ptr = new M(key, std::forward<Args>(args)...);
      metrics_[key] = std::unique_ptr<M>(metric_ptr);
      return *metric_ptr;
    }
  }
};

};  // namespace telemetry

#endif  // METALHEART_TELEMETRY_METRIC_REGISTRY_H