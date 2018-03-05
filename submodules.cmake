#Constants
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodule)


set(glfw3_DIR ${LIB_DIR}/glfw)
#GLM
set(GLM_INCLUDE "${LIB_DIR}/glm")

#IMGUI
set(IMGUI "${LIB_DIR}/imgui")

ADD_LIBRARY( IMGUI_LIB STATIC IMPORTED
        ${IMGUI}/imgui.h ${IMGUI}/imgui.cpp ${IMGUI}/imgui_draw.cpp
        ${IMGUI}/imgui_internal.h ${IMGUI}/imconfig.h ${IMGUI}/stb_rect_pack.h
        ${IMGUI}/stb_textedit.h ${IMGUI}/stb_truetype.h )

#GLFW
set(GLFW_INCLUDE ${LIB_DIR}/glfw/include)
set(GLFW_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/glfw/src/libglfw3dll.a)

#GLBINDING
set(GLBINDING_INCLUDE ${LIB_DIR}/glbinding/source/glbinding/include
        temp/glbinding/source/glbinding/include)
set(GLBINDING_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/glbinding/libglbinding.a)

#assimp
set(ASSIMP_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/code/libassimp.dll.a)
set(ASSIMP_INCLUDE ${LIB_DIR}/assimp/include ${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/include)

#chaiscript
set(CHAI_INCLUDE ${LIB_DIR}/chaiscript/include)
set(CHAI_LIB ${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript/libstdlib.a
        ${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript/libparser.a)


#soil
set(SOIL ${LIB_DIR}/soil/src)
set(SOIL_INCLUDE ${SOIL})

set(SOIL_SOURCES
        ${SOIL}/image_DXT.c ${SOIL}/image_DXT.h
        ${SOIL}/image_helper.c ${SOIL}/image_helper.h
        ${SOIL}/SOIL.c ${SOIL}/SOIL.h
        ${SOIL}/stb_image_aug.c ${SOIL}/stb_image_aug.h
        ${SOIL}/stbi_DDS_aug_c.h ${SOIL}/stbi_DDS_aug.h
        )

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
        ${ASSIMP_LIB}
        ${CHAI_LIB}
        ${IMGUI_LIB}
        )


set(ARGUMENTS
        -fpermissive
        -static-libstdc++
        -static-libgcc
        -lopengl32
        -lglu32
        -lz
        -lgdi32
        -Wwrite-strings
   )