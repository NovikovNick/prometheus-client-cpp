add_executable(telemetry_test
  counter_test.cc
)

target_link_libraries(telemetry_test
  PRIVATE
    lib::${PROJECT_NAME}
    GTest::gmock_main
)

add_test(
  NAME telemetry_test
  COMMAND telemetry_test
)