#Settings
project(proton)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-O0)
#add_definitions(-pg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module")

set(INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_definitions(-DEXPORT_LIB)

#Linking
set(SOURCE_FILES src/interface/display/Display.cpp
        include/interface/Display.h src/engine/Proton.cpp
        include/Proton.h include/DisplaySettings.h
        src/engine/component/Transform.cpp include/component/Transform.h
        src/interface/io/FileLoader.cpp include/io/FileLoader.h
        src/engine/component/Renderer.cpp include/component/Renderer.h
        src/interface/graphics/Shader.cpp include/interface/Shader.h
        src/interface/graphics/Buffer.cpp include/interface/Buffer.h
        src/engine/component/Component.cpp include/component/Component.h
        src/engine/entity/Entity.cpp include/entity/Entity.h
        src/interface/graphics/IndexBuffer.cpp include/interface/IndexBuffer.h
        src/interface/graphics/VertexArray.cpp include/interface/VertexArray.h
        src/engine/Scene.cpp include/Scene.h src/engine/entity/Camera.cpp include/entity/Camera.h
        src/engine/component/DemoComponent.cpp src/engine/component/DemoComponent.h src/engine/component/Move.cpp
        src/engine/component/Move.h src/interface/graphics/Uniform.cpp include/interface/Uniform.h
        src/interface/graphics/Texture.cpp include/interface/Texture.h include/CustomEvent.h include/EventManager.h
        src/interface/io/EventManager.cpp include/io/Input.h src/interface/io/Input.cpp include/interface/GUI.h src/interface/GUI.cpp
        )


include(submodules.cmake)
include(cmake/dependencies.cmake)
add_library(proton SHARED ${SOURCE_FILES} ${IMGUI_SOURCES})
target_compile_definitions(proton PRIVATE EXPORT_LIB=1)

#add_executable(proton ${SOURCE_FILES} ${IMGUI_SOURCES} ${SOIL_SOURCES})

target_link_libraries(proton ${LINKER} ${ARGUMENTS} -pg)

