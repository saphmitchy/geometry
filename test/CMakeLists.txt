cmake_minimum_required(VERSION 3.11)
project(geomtry)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

add_executable(configTest config_test.cpp)
target_link_libraries(configTest gtest_main)
gtest_discover_tests(configTest)