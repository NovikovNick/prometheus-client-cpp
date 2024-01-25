#include <gtest/gtest.h>
#include <telemetry/api.h>

namespace telemetry {
namespace {

TEST(DifferentTypeTest, collectTest) {
  EXPECT_EXIT(
      {
        counter()  //
            .name("DifferentTypeTest")
            .measure(1);
        histogram()  //
            .name("DifferentTypeTest")
            .buckets(0.5, 1, 10)
            .measure(1);
      },
      testing::KilledBySignal(SIGABRT),
      "");
}

}  // namespace
}  // namespace telemetry