#include <benchmark/benchmark.h>
#include <telemetry/api.h>

static void BM_Histogram_Preinited(benchmark::State &state) {
  auto &metric = telemetry::histogram()  //
                     .name("BM_Histogram_Preinited")
                     .buckets(0.5, 1.0, 2.0)
                     .get();
  while (state.KeepRunning()) {
    metric.measure(1);
  }
}
BENCHMARK(BM_Histogram_Preinited);

static void BM_Histogram_Dynamic(benchmark::State &state) {
  while (state.KeepRunning()) {
    telemetry::histogram()  //
        .name("BM_Histogram_Dynamic")
        .buckets(0.5, 1.0, 2.0)
        .measure(1);
  }
}
BENCHMARK(BM_Histogram_Dynamic);