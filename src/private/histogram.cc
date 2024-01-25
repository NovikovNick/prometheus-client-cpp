#include "histogram.h"

#include <cassert>
#include <cmath>
#include <format>

namespace telemetry {

namespace {}

Histogram::Histogram(const MetricKey& key, const std::vector<double>& buckets)
    : Metric(Type::Histogram, key),
      sum(0),
      metric_description_(""),
      metric_sum_(""),
      metric_count_("") {
  for (auto bucket : buckets) {
    buckets_[bucket] = 0;
  }
};

void Histogram::measure(double value) {
  std::unique_lock lock(mutex_);
  for (auto& [backet, counter] : buckets_) {
    if (value <= backet) {
      ++counter;
      sum += value;
      return;
    }
  }
  assert(false);
}

std::map<double, int64_t> Histogram::value() {
  std::unique_lock lock(mutex_);
  return buckets_;
};

void Histogram::collect(std::string& out) {
  if (metric_description_.empty()) {
    metric_description_ = std::format(
        "# HELP {} {}\n"
        "# TYPE {} histogram\n",
        key_.name,
        key_.description,
        key_.name);
    metric_sum_   = std::format("{}_sum ", key_.name);
    metric_count_ = std::format("{}_count ", key_.name);

    for (auto [backet, _] : buckets_) {
      buckets_metric_description_[backet] =
          key_.name    //
          + "_bucket"  //
          + labelsToString({{"le", std::to_string(backet)}});
    }
  }

  out += metric_description_;

  size_t count = 0;

  auto lk = std::unique_lock(mutex_);

  for (auto [backet, counter] : buckets_) {
    count += counter;
    out += buckets_metric_description_[backet];
    out += ' ' + std::to_string(counter) + '\n';
  }
  out += metric_sum_ + std::to_string(sum) + '\n';
  out += metric_count_ + std::to_string(count) + '\n';
};
}  // namespace telemetry
