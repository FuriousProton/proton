#Settings
project(proton)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)

option(DEPENDENCY "Make a specific thing" OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module")

set(INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")

#Linking
set(SOURCE_FILES src/main.cpp src/interface/display/Display.cpp
        src/interface/display/Display.h src/engine/Proton.cpp src/engine/Proton.h
        src/engine/DisplaySettings.h
        src/engine/component/Transform.cpp src/engine/component/Transform.h)
include(submodules.cmake)
include(cmake/dependencies.cmake)


add_executable(proton ${SOURCE_FILES} ${IMGUI_SOURCES})

target_link_libraries(proton ${LINKER} ${ARGUMENTS})

MESSAGE( STATUS "dependency: " ${DEPENDENCY} )
