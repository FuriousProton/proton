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


ExternalProject_Add_Step(
        glfw_module CopyToBin
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/temp/glfw/src/glfw3.dll" $<TARGET_FILE_DIR:proton>
        DEPENDEES install
)
#add_definitions(-O1)

ExternalProject_Add(assimp_module
        GIT_SUBMODULES "submodule/assimp"
        DOWNLOAD_COMMAND git submodule update --recursive
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodule/assimp"
        BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp"
        CMAKE_ARGS
        -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
#        -DENABLE_BOOST_WORKAROUND=ON
        -DASSIMP_BUILD_TESTS=OFF
#        -DBUILD_SHARED_LIBS=OFF
        -DASSIMP_BUILD_NO_OWN_ZLIB=ON
        -DASSIMP_BUILD_NO_IFC_IMPORTER=OFF
        -DASSIMP_NO_EXPORT=ON
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )


ExternalProject_Add_Step(
        assimp_module CopyToBin
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/temp/assimp/code/libassimp.dll" $<TARGET_FILE_DIR:proton>
        DEPENDEES install
)


ExternalProject_Add(chai_module
        GIT_SUBMODULES "submodule/glfw"
        DOWNLOAD_COMMAND git submodule update --recursive
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodule/chaiscript"
        BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/temp/chaiscript"
        CMAKE_ARGS
        -DUNIT_TEST_LIGHT=ON
        -DRUN_PERFORMANCE_TESTS=OFF
        -DRUN_FUZZY_TESTS=OFF
        -DBUILD_TESTING=OFF
        -DBUILD_MODULES=OFF
        -DBUILD_SAMPLES=OFF
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
#
#ExternalProject_Add(soil_module
#    GIT_SUBMODULES "submodule/soil-make"
#    DOWNLOAD_COMMAND git submodule update --recursive
#    UPDATE_COMMAND ""
#    PATCH_COMMAND ""
#    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodule/soil-make"
#    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/temp/soil"
#    CONFIGURE_COMMAND ""
#
#    BUILD_COMMAND
#    INSTALL_COMMAND ""
#    TEST_COMMAND ""
#  )
#
