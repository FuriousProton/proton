#Settings
project(proton)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)

#add_definitions(-O1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module")

set(INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")

#Linking
set(SOURCE_FILES src/main.cpp src/interface/display/Display.cpp
        src/interface/display/Display.h src/engine/Proton.cpp
        src/engine/Proton.h src/engine/DisplaySettings.h
        src/engine/component/Transform.cpp src/engine/component/Transform.h
        src/interface/io/FileLoader.cpp src/interface/io/FileLoader.h
        src/engine/component/Renderer.cpp src/engine/component/Renderer.h
        src/interface/graphics/Shader.cpp src/interface/graphics/Shader.h
        src/interface/graphics/Buffer.cpp src/interface/graphics/Buffer.h
        src/engine/component/Component.cpp src/engine/component/Component.h
        src/engine/entity/Entity.cpp src/engine/entity/Entity.h
        src/interface/graphics/IndexBuffer.cpp src/interface/graphics/IndexBuffer.h
        src/interface/graphics/VertexArray.cpp src/interface/graphics/VertexArray.h
        src/engine/Scene.cpp src/engine/Scene.h src/engine/entity/Camera.cpp src/engine/entity/Camera.h src/engine/component/DemoComponent.cpp src/engine/component/DemoComponent.h)
include(submodules.cmake)
include(cmake/dependencies.cmake)


add_executable(proton ${SOURCE_FILES} ${IMGUI_SOURCES})

target_link_libraries(proton ${LINKER} ${ARGUMENTS})

