add_executable(prometheus_core_test
  counter_test.cc
)

target_link_libraries(prometheus_core_test
  PRIVATE
    lib::${PROJECT_NAME}
    GTest::gmock_main
)

add_test(
  NAME prometheus_core_test
  COMMAND prometheus_core_test
)