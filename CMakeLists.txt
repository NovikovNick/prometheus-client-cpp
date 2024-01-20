cmake_minimum_required(VERSION 3.10)
project (telemetry
    LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Wpedantic)

option(ENABLE_TESTS         "Enable unit tests" OFF)
option(ENABLE_BENCHMARKS    "Enable benchmarks" OFF)

if(ENABLE_TESTS)
  find_package(GTest 1.11 CONFIG REQUIRED)
  enable_testing()
  add_subdirectory(test)
endif()

if(ENABLE_BENCHMARKS)
  find_package(benchmark CONFIG)
  add_subdirectory(benchmark)
endif()

set(TELEMETRY_SRC 
    src/private/counter.cc
    src/private/gauge.cc
    src/private/histogram.cc
    src/private/summary.cc)

add_library                 (${PROJECT_NAME} STATIC ${TELEMETRY_SRC})
add_library                 (lib::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_features     (${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories  (${PROJECT_NAME} 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/public
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/public
)

message(STATUS "")
message(STATUS "Prometheus client configuration summary:")
message(STATUS "")
message(STATUS "  CMake build type ...................: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Enable unit tests ..................: ${ENABLE_TESTS}")
message(STATUS "  Enable unit benchmarks .............: ${ENABLE_BENCHMARKS}")
message(STATUS "")