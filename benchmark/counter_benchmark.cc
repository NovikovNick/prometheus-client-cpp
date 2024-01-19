#include <benchmark/benchmark.h>
#include <telemetry/api.h>

static void BM_Counter_Preinited(benchmark::State &state) {
  auto &metric = telemetry::counter()  //
                     .name("BM_Counter_Preinited")
                     .get();
  while (state.KeepRunning()) {
    metric.measure(1);
  }
}
BENCHMARK(BM_Counter_Preinited);

static void BM_Counter_Dynamic(benchmark::State &state) {
  while (state.KeepRunning()) {
    telemetry::counter()  //
        .name("BM_Counter_Preinited")
        .measure(1);
  }
}
BENCHMARK(BM_Counter_Dynamic);