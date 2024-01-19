#include "counter.h"

#include <cmath>
#include <format>

namespace telemetry {

void Counter::increment() { measure(1.0); }

int Counter::value() const { return static_cast<int>(value_.load()); };

void Counter::measure(double value) {
  value_.fetch_add(static_cast<int>(value));
};

void Counter::collect(std::string& out) {
  out += std::format("# HELP {} {}\n", key_.name, key_.description);
  out += std::format("# TYPE {} counter\n", key_.name);
  out += std::format("{}", key_.name);
  collectTags(out);
  out += std::format(" {}\n", value_.load());
};
}  // namespace telemetry
