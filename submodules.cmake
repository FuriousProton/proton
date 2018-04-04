#Constants
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodule)


#set(glfw3_DIR ${LIB_DIR}/glfw)
#GLM
set(GLM_INCLUDE "${LIB_DIR}/glm")

find_package(glfw3 REQUIRED)

find_package(glbinding REQUIRED)

#GLFW
#set(GLFW_INCLUDE ${LIB_DIR}/glfw/include)
#set(GLFW_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/glfw/src/libglfw3dll.a)

#add_library(glbinding STATIC IMPORTED)

#GLBINDING
#[[set(GLBINDING_INCLUDE ${LIB_DIR}/glbinding/source/glbinding/include
        temp/glbinding/source/glbinding/include)
set(GLBINDING_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/glbinding/libglbinding.a)]]

##assimp
#set(ASSIMP_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/code/libassimp.dll.a)
#set(ASSIMP_INCLUDE ${LIB_DIR}/assimp/include ${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/include)

#chaiscript
set(CHAI_INCLUDE ${LIB_DIR}/chaiscript/include)
set(CHAI_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript/libstdlib.a
        ${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript/libparser.a)


#soil
#set(ASSIMP_INCLUDE ${LIB_DIR}/soil/inc)
#set(SOIL_LIB ${LIB_DIR}/soil/lib/libSOIL.a)
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
include_directories(
        ${GLM_INCLUDE}
        ${GLBINDING_INCLUDE}
        ${GLFW_INCLUDE}
        ${CHAI_INCLUDE}
        ${ASSIMP_INCLUDE}
        ${SOIL_INCLUDE}
)

set(LINKER
        ${GLBINDING_LIB}
        ${GLFW_LIB}
        ${SOIL_LIB}
        ${ASSIMP_LIB}
        ${CHAI_LI}
#        ${glbinding}
        ${SOIL_LIB}
        )

if(WIN32)
    set(ARGUMENTS
        -fpermissive
        -static-libstdc++
        -static-libgcc
        -lSOIL
        -lopengl32
        -lglu32
        -lz
        -lgdi32
        -lassimp
        -Wwrite-strings
    )
    ELSE()
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
ENDIF()