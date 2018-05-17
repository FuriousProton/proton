#Constants
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodule)


#set(glfw3_DIR ${LIB_DIR}/glfw)
#GLM
set(GLM_INCLUDE "${LIB_DIR}/glm")

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

find_package(glbinding REQUIRED)
if (WIN32)

    #GLFW
    #[[set(GLFW_INCLUDE ${LIB_DIR}/glfw/include)
    set(GLFW_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/glfw/src/libglfw3dll.a)]]

    #add_library(glbinding STATIC IMPORTED)

    #GLBINDING
    #[[set(GLBINDING_INCLUDE ${LIB_DIR}/glbinding/source/glbinding/include
            temp/glbinding/source/glbinding/include)
    set(GLBINDING_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/glbinding/libglbinding.a)]]
endif ()
##assimp
#set(ASSIMP_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/code/libassimp.dll.a)
#set(ASSIMP_INCLUDE ${LIB_DIR}/assimp/include ${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/include)

#chaiscript
set(CHAI_INCLUDE ${LIB_DIR}/chaiscript/include)
set(CHAI_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript/libstdlib.a
        ${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript/libparser.a)

##IMGUI
set(IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui)
set(IMGUI_SOURCES ${IMGUI_PATH}/imconfig.h ${IMGUI_PATH}/imgui.cpp ${IMGUI_PATH}/imgui.h
        ${IMGUI_PATH}/imgui_draw.cpp ${IMGUI_PATH}/imgui_internal.h
        ${IMGUI_PATH}/imgui_dock.cpp ${IMGUI_PATH}/imgui_dock.h
        ${IMGUI_PATH}/imgui_impl_glfw_gl3.cpp ${IMGUI_PATH}/imgui_impl_glfw_gl3.h)



#soil
#set(ASSIMP_INCLUDE ${LIB_DIR}/soil/inc)
#set(SOIL_LIB ${LIB_DIR}/soil/lib/libSOIL.a)
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach ()
include_directories(
        ${GLM_INCLUDE}
        ${CHAI_INCLUDE}
        ${ASSIMP_INCLUDE}
        ${SOIL_INCLUDE}
)

set(LINKER
        ${SOIL_LIB}
        ${ASSIMP_LIB}
        ${CHAI_LI}
        ${SOIL_LIB}
        ${GLFW3_LIBRARY}
        )

if (WIN32)
    set(ARGUMENTS
            -fpermissive
            -static-libstdc++
            -static-libgcc
            -lSOIL
            -lopengl32
            -lglu32
            glbinding::glbinding

            -lz
            -lgdi32
            -lassimp
            -Wwrite-strings
            )
ELSE ()
    set(ARGUMENTS
            -fpermissive
            -static-libstdc++
            -static-libgcc
            -lSOIL
            -lGL
            -lGLU
            -lz
            glfw
            #            -lgdi32
            -lassimp
            -Wwrite-strings
            glbinding::glbinding
            )
ENDIF ()

get_cmake_property(_variableNames VARIABLES)
list(SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach ()
