include(ExternalProject)
ExternalProject_Add(glfw_module
        GIT_SUBMODULES "submodule/glfw"
        DOWNLOAD_COMMAND git submodule update --recursive
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodule/glfw"
        BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/temp/glfw"
        CMAKE_ARGS -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
        -DGLFW_INSTALL=OFF
        -DBUILD_SHARED_LIBS=ON
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )
#[[
add_custom_command(TARGET glfw_module POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different     # which executes "cmake - E copy_if_different..."
        "${CMAKE_CURRENT_SOURCE_DIR}/temp/glfw/src/glfw3.dll"                   # <--this is in-file
        $<TARGET_FILE_DIR:proton>)                 # <--this is out-file path

]]

ExternalProject_Add(assimp_module
        GIT_SUBMODULES "submodule/assimp"
        DOWNLOAD_COMMAND git submodule update --recursive
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodule/assimp"
        BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp"
        CMAKE_ARGS
        -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
        -DASSIMP_BUILD_TESTS=OFF
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )
#[[
add_custom_command(TARGET assimp_module POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different     # which executes "cmake - E copy_if_different..."
        "${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/code/libassimp.dll"                   # <--this is in-file
        $<TARGET_FILE_DIR:proton>)                 # <--this is out-file path

]]

ExternalProject_Add(chai_module
        GIT_SUBMODULES "submodule/glfw"
        DOWNLOAD_COMMAND git submodule update --recursive
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodule/chaiscript"
        BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript"
        CMAKE_ARGS
        -DUNIT_TEST_LIGHT=ON
        -DBUILD_MODULES=OFF
#        -DMULTITHREAD_SUPPORT_ENABLED=FALSE
        -DDYNLOAD_ENABLED=FALSE
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )


ExternalProject_Add(glbinding_module
        GIT_SUBMODULES "submodule/glbinding"
        DOWNLOAD_COMMAND git submodule update --recursive
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodule/glbinding"
        BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/temp/glbinding"
        CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
        -DOPTION_BUILD_TESTS=OFF
        -DOPTION_BUILD_GPU_TESTS=OFF
        -DOPTION_BUILD_TOOLS=OFF
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )