#include <benchmark/benchmark.h>
#include <telemetry/api.h>

static void BM_Gauge_Preinited(benchmark::State &state) {
  auto &metric = telemetry::gauge()  //
                     .name("BM_Gauge_Preinited")
                     .get();
  while (state.KeepRunning()) {
    metric.measure(1);
  }
}
BENCHMARK(BM_Gauge_Preinited);

static void BM_Gauge_Dynamic(benchmark::State &state) {
  telemetry::gauge()  //
      .name("BM_Gauge_Dynamic")
      .measure(0);
  while (state.KeepRunning()) {
    telemetry::gauge()  //
        .name("BM_Gauge_Dynamic")
        .measure(1);
  }
}
BENCHMARK(BM_Gauge_Dynamic);