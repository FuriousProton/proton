#Constants
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodule)

#GLEW
set(GLEW_INCLUDE "${LIB_DIR}/glew/include")
add_subdirectory(${LIB_DIR}/glew/build/cmake)
set(GLEW_LIB "${LIB_DIR}/glew/lib/libglew32.a")


#GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${LIB_DIR}/glfw")
set(GLFW_INCLUDE "${LIB_DIR}/glfw/include")

#GLM
set(GLM_INCLUDE "${LIB_DIR}/glm")

#IMGUI
set(IMGUI "${LIB_DIR}/imgui")
set(IMGUI_SOURCES ${IMGUI}/imgui.h ${IMGUI}/imgui.cpp ${IMGUI}/imgui_draw.cpp
        ${IMGUI}/imgui_internal.h ${IMGUI}/imconfig.h ${IMGUI}/stb_rect_pack.h
        ${IMGUI}/stb_textedit.h ${IMGUI}/stb_truetype.h)

add_definitions(-DGLEW_STATIC)
add_library(glew_static STATIC IMPORTED)
set_target_properties(glew_static PROPERTIES
        IMPORTED_LOCATION ${GLEW_LIB})

link_directories(${GLFW_LIB})

include_directories(${GLM_INCLUDE} ${GLEW_INCLUDE})
add_subdirectory(${GLM_INCLUDE})


set(LINKER glfw glew_static)

set(ARGUMENTS
        -static-libstdc++
        -lopengl32
        -lglu32
        -lgdi32
   )