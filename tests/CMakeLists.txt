cmake_minimum_required(VERSION 3.20)

if("${TARGET_PLATFORM}" STREQUAL "UNIT_TESTS")

add_library(CppUTestRunner INTERFACE)
target_sources(CppUTestRunner INTERFACE cpputest_runner.cpp)

add_unit_test(template_test template_test.cpp)

endif()