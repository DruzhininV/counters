cmake_minimum_required(VERSION 3.26)
project(counters)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp)

target_sources(${PROJECT_NAME}
        PRIVATE
        index_range.h
        index_range.cpp
        counter_array.h
        counter_array.cpp
        metric_storage.h
        metric_storage.cpp
)
