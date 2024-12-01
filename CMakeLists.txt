# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.5)
project (OnlineStatisticsProject)

# Build in release mode by default
if (NOT CMAKE_BUILD_TYPE)
    message("MAKE_BUILD_TYPE unset, set CMAKE_BUILD_TYPE=Release")
    set(CMAKE_BUILD_TYPE Release CACHE INTERNAL "")
endif()

set(CMAKE_C_STANDARD                99)
# use C++23 so as to allow use of <format> and <zip> in tests.
# OnlineStatistics itself only .
set(CMAKE_CXX_STANDARD              23)

# Make the standard a requirement => prevent fallback to previous
# supported standard
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)

# We want to pass standard C/C++ flags, without gnu extensions
set(CMAKE_C_EXTENSIONS              OFF)
set(CMAKE_CXX_EXTENSIONS            OFF)


SET(sources
    src/OnlineStatistics.cpp
    inc/OnlineStatistics.h
)
add_library(OnlineStatistics ${sources})

target_include_directories(OnlineStatistics PUBLIC "inc")

# This allows to include files relative to the root of the src directory with a <> pair
find_package(Catch2 3 REQUIRED)

# test
SET(sources_test tests/TestOnlineStatistics.cpp)
add_executable(tests ${sources_test})
target_link_libraries(tests PRIVATE OnlineStatistics Catch2::Catch2WithMain)

# example
add_executable(example examples/example.cpp inc/OnlineStatistics.h)
target_link_libraries(example PRIVATE OnlineStatistics)
