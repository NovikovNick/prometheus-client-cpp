# Prometheus client cpp

Work in progress...

## Usage
``` c++
#include <telemetry/api.h>

telemetry::summary()
    .name("your_service_http_request_duration_seconds")
    .tag("path", "/foo/bar")
    .description("A summary of the http request duration.")
    .observation_time(minutes{1})
    .quantiles(0.5, 0.9, 0.95, 1.0)
    .measure(0.42);

telemetry::gauge()
    .name("your_service_http_request_count")
    .description("Total http requests")
    .measure(42);
```

## License

MIT