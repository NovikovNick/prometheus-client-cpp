#include <benchmark/benchmark.h>
#include <telemetry/api.h>

static void BM_Collect(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::string out;
    telemetry::collect(out);
  }
}
BENCHMARK(BM_Collect);
