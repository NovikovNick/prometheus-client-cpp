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
  telemetry::counter()  //
      .name("BM_Counter_Dynamic")
      .measure(0);
  while (state.KeepRunning()) {
    telemetry::counter()  //
        .name("BM_Counter_Dynamic")
        .measure(1);
  }
}
BENCHMARK(BM_Counter_Dynamic);

static void BM_Counter_Creation(benchmark::State &state) {
  int i = 0;
  while (state.KeepRunning()) {
    telemetry::counter()  //
        .name("BM_Counter_Dynamic#" + std::to_string(++i))
        .measure(0);
  }
}
BENCHMARK(BM_Counter_Creation);