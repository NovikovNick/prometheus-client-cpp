add_executable(benchmarks
  main.cc
  counter_benchmark.cc
  gauge_benchmark.cc
  histogram_benchmark.cc
  summary_benchmark.cc
  standart_operations_benchmark.cc
)

target_link_libraries(benchmarks
  PRIVATE
    lib::${PROJECT_NAME}
    benchmark::benchmark
)

add_test(
  NAME benchmarks
  COMMAND benchmarks
)

set_property(
  TEST benchmarks
  APPEND PROPERTY LABELS Benchmark
)