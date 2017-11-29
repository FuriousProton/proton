project(proton.imaging)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-O1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_