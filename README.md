# Prometheus client cpp

Work in progress...

## Build with CMake on *nix system

```shell
git clone https://github.com/NovikovNick/prometheus-client-cpp.git -b develop
cd prometheus-client-cpp        # Main directory of the cloned repository.
mkdir build                     # Create a directory to hold the build output.
cd build
cmake ..                        # Generate native build scripts for project.
make
```

## Usage
``` c++
#include <telemetry/api.h>

// Dynamic metric can be useful to track all http url in tags
telemetry::summary()
    .name("your_service_http_request_duration_seconds")
    .tag("path", url)
    .description("A summary of the http request duration.")
    .observation_time(minutes{1})
    .quantiles(0.5, 0.9, 0.95, 1.0)
    .measure(0.42);

// ...but preinited metric is an order of magnitude cheaper
auto& metric_summary = telemetry::summary()
    .name("your_service_http_request_duration_seconds")
    .tag("path", "/foo/bar")
    .description("A summary of the http request duration.")
    .observation_time(minutes{1})
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

auto& http_duration_sec = telemetry::histogram()
    .name("your_service_http_request_duration_seconds")
    .description("Total http requests")
    .backets(0.1, 1.0, 5.0)
    .get();

request_count.measure(1);
rss.measure(42);
metric_histogram.measure(0.42);
```

## Benchmarks and tests
1. Enable in CMake option ENABLE_TESTS
2. Install <https://github.com/google/googletest>
3. Install <https://github.com/google/benchmark>

## License

MIT