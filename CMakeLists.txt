#Settings
cmake_minimum_required(VERSION 3.8)
project(proton)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#Linking
set(SOURCE_FILES main.cpp)


set(LINKER)
set(ARGUMENTS
        -static-libstdc++
        -lopengl32 -lglu32 -lgdi32
        )

add_executable(proton ${SOURCE_FILES})


target_link_libraries(proton ${LINKER} ${ARGUMENTS})
