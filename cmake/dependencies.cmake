include(ExternalProject)
ExternalProject_Add(glfw
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
add_custom_command(TARGET glfw POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different     # which executes "cmake - E copy_if_different..."
        "${CMAKE_CURRENT_SOURCE_DIR}/temp/glfw/src/glfw3.dll"                   # <--this is in-file
        $<TARGET_FILE_DIR:proton>)                 # <--this is out-file path


ExternalProject_Add(glbinding
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