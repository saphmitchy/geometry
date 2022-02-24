cmake_minimum_required(VERSION 3.11)
project(geomtry)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)

add_executable(configTest config_test.cpp)
target_link_libraries(configTest gtest_main)
gtest_discover_tests(configTest)

add_executable(pointTest point_test.cpp)
target_link_libraries(pointTest gtest_main)
gtest_discover_tests(pointTest)

add_executable(lineTest line_test.cpp)
target_link_libraries(lineTest gtest_main)
gtest_discover_tests(lineTest)

add_executable(segmentTest segment_test.cpp)
target_link_libraries(segmentTest gtest_main)
gtest_discover_tests(segmentTest)

add_executable(rayTest ray_test.cpp)
target_link_libraries(rayTest gtest_main)
gtest_discover_tests(rayTest)

add_executable(circleTest circle_test.cpp)
target_link_libraries(circleTest gtest_main)
gtest_discover_tests(circleTest)

add_executable(intersectionTest intersection_test.cpp)
target_link_libraries(intersectionTest gtest_main)
gtest_discover_tests(intersectionTest)