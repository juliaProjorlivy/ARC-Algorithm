cmake_minimum_required(VERSION 3.13)
project(ARC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(arc STATIC include/arc/arc.hpp include/arc/io.hpp src/arc/io.cpp)
target_include_directories(arc PUBLIC include/arc)

add_library(pcache INTERFACE)
target_include_directories(pcache INTERFACE include/pcache)

add_subdirectory(src/arc)
add_subdirectory(src/pcache)

option(TEST_BUILD "" ON)
if(TEST_BUILD)
message(STATUS "Building test...")
add_subdirectory(tests)
endif()

