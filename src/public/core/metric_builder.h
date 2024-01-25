#ifndef METALHEART_TELEMETRY_METRIC_BUILDER_H
#define METALHEART_TELEMETRY_METRIC_BUILDER_H

#include <concepts>
#include <string>

#include "metric.h"
#include "metric_key.h"
#include "metric_registry.h"

namespace telemetry {

template <std::derived_from<Metric> M, typename Self>
struct MetricBuilder {
  MetricKey key_;

 public:
  Self& name(std::string_view name) {
    key_.name = name;
    return static_cast<Self&>(*this);
  };

  Self& description(std::string_view description) {
    key_.description = description;
    return static_cast<Self&>(*this);
  };

  Self& label(std::string_view key, std::string_view value) {
    key_.labels[std::string{key}] = value;
    return static_cast<Self&>(*this);
  };

  virtual void measure(double value) = 0;

  virtual M& get() = 0;

  virtual ~MetricBuilder() = default;

 protected:
  template <typename... Args>
  M& build(Metric::Type type, Args&&... args) {
    return MetricRegistry::instance()  //
        .ensureExist<M>(type, key_, std::forward<Args>(args)...);
  }
};

}  // namespace telemetry
#endif  // METALHEART_TELEMETRY_METRIC_BUILDER_H
