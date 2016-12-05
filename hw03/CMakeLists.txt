cmake_minimum_required(VERSION 3.5)
project(hw03_accounting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

# accounting sources
file(GLOB SOURCES ./*.hpp ./*.cpp)
add_library(accounting ${SOURCES})

# console application
add_executable(accounting-cli main.cpp)
target_link_libraries(accounting-cli accounting)

# testing
add_subdirectory(libs/googletest)
include_directories(libs/googletest/include libs/googletest)
file(GLOB TEST_SOURCES tests/*.hpp tests/*.cpp)
add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests accounting)
