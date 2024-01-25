#include <gtest/gtest.h>
#include <telemetry/api.h>

#include <iostream>

namespace telemetry {
namespace {

TEST(HistogramTest, first_bucket) {
  // arrange
  Histogram& metric = histogram()  //
                          .name("HistogramTest1")
                          .buckets(0.5, 1, 10)
                          .get();

  // act
  metric.measure(0.4);
  auto value = metric.value();

  // assert
  EXPECT_EQ(1, value[0.5]);
  EXPECT_EQ(0, value[1]);
  EXPECT_EQ(0, value[10]);
}

TEST(HistogramTest, second_bucket) {
  // arrange
  Histogram& metric = histogram()  //
                          .name("HistogramTest2")
                          .buckets(0.5, 1, 10)
                          .get();

  // act
  metric.measure(1);
  auto value = metric.value();

  // assert
  EXPECT_EQ(0, value[0.5]);
  EXPECT_EQ(1, value[1]);
  EXPECT_EQ(0, value[10]);
}

TEST(HistogramTest, third_bucket) {
  // arrange
  Histogram& metric = histogram()  //
                          .name("HistogramTest3")
                          .buckets(0.5, 1, 10)
                          .get();

  // act
  metric.measure(5);
  auto value = metric.value();

  // assert
  EXPECT_EQ(0, value[0.5]);
  EXPECT_EQ(0, value[1]);
  EXPECT_EQ(1, value[10]);
}

}  // namespace
}  // namespace telemetry