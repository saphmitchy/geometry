cmake_minimum_required(VERSION 3.11)
project(geomtry)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_executable(crossPointTest cross_point_test.cpp)
target_link_libraries(crossPointTest gtest_main)
gtest_discover_tests(crossPointTest)

add_executable(distanceTest distance_test.cpp)
target_link_libraries(distanceTest gtest_main)
gtest_discover_tests(distanceTest)

add_executable(tangentTest tangent_test.cpp)
target_link_libraries(tangentTest gtest_main)
gtest_discover_tests(tangentTest)

add_executable(polygonTest polygon_test.cpp)
target_link_libraries(polygonTest gtest_main)
gtest_discover_tests(polygonTest)
