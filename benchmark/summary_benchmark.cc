#include <benchmark/benchmark.h>
#include <telemetry/api.h>

static void BM_Summary_Preinited(benchmark::State &state) {
  auto &metric = telemetry::summary()  //
                     .name("BM_Summary_Preinited")
                     .quantiles(0.5, 0.9)
                     .get();
  while (state.KeepRunning()) {
    metric.measure(1);
  }
}
BENCHMARK(BM_Summary_Preinited);

static void BM_Summary_Dynamic(benchmark::State &state) {
  telemetry::summary()  //
      .name("BM_Summary_Dynamic")
      .quantiles(0.5, 0.9)
      .measure(0);

  while (state.KeepRunning()) {
    telemetry::summary()  //
        .name("BM_Summary_Dynamic")
        .quantiles(0.5, 0.9)
        .measure(1);
  }
}
BENCHMARK(BM_Summary_Dynamic);