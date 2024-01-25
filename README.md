# Prometheus client cpp

Work in progress...

## Build with CMake on *nix system
Required: gcc 13

```shell
git clone https://github.com/NovikovNick/prometheus-client-cpp.git -b develop
cd prometheus-client-cpp                                   # Main directory of the cloned repository.
mkdir build                                                # Create a directory to hold the build output.
cd build
cmake .. -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++-13     # Generate native build scripts for project.
make
```

## Usage
```c++
#include <telemetry/api.h>

// Dynamic metric can be useful to track some dynamic data in labels
  telemetry::summary()
      .name("your_service_http_request_duration_seconds")
      .label("path", url)
      .description("A summary of the http request duration.")
      .sliding_time_window(minutes{1})
      .quantiles(0.5, 0.9, 0.95, 1.0)
      .measure(0.42);

  // ...but preinited metric is an order of magnitude cheaper
  auto& metric_summary =
      telemetry::summary()
          .name("your_service_http_request_duration_seconds")
          .label("path", "/foo/bar")
          .description("A summary of the http request duration.")
          .sliding_time_window(minutes{1})
          .quantiles(0.5, 0.9, 0.95, 1.0)
          .get();
  metric_summary.measure(0.42);

  // other metrics

  auto& request_count = telemetry::counter()
                            .name("your_service_http_request_count")
                            .description("Total http requests")
                            .get();

  auto& rss = telemetry::gauge()
                  .name("your_service_memory_consumtion")
                  .description("Memory consumption")
                  .get();

  auto& http_duration_sec =
      telemetry::histogram()
          .name("your_service_http_request_duration_seconds")
          .description("Total http requests")
          .buckets(0.1, 1.0, 5.0)
          .get();

  request_count.measure(1);
  rss.measure(42);
  http_duration_sec.measure(0.42);

  // write prometheus data for endpoint /metrics
  std::string out;
  telemetry::collect(out);
  output_stream << out;
```

## Tests
1. Install <https://github.com/google/googletest>
2. ```mkdir build && cd build```
2. ```cmake .. -DENABLE_TESTS=ON -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++-13```
3. ```make```
6. Run ```./test/telemetry_test```

## Benchmarks
1. Install <https://github.com/google/benchmark>
2. ```mkdir build && cd build```
2. ```cmake .. -DENABLE_BENCHMARKS=ON -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++-13```
3. ```make```
3. Run ```./benchmark/benchmarks```

## License

MIT