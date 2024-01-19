#include <gtest/gtest.h>
#include <telemetry/api.h>

namespace telemetry {
namespace {

TEST(CounterTest, initialize_with_zero) {
  // arrange
  Counter& metric = counter().name("test").get();
  // act
  // nothing
  // assert
  EXPECT_EQ(0, metric.value());
}

TEST(CounterTest, measure_calling) {
  // arrange
  Counter& metric = counter().name("test").get();

  // act
  metric.measure(1);
  metric.measure(2);
  metric.measure(3);

  // assert
  EXPECT_EQ(6, metric.value());
}

}  // namespace
}  // namespace telemetry