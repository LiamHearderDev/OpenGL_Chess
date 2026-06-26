include(ExternalProject)
ExternalProject_Add(stb_external
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_SHALLOW ON
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${EP_SOURCE_DIR_PREFIX}/stb_external ${STAGED_INSTALL_PREFIX}/include/stb
    BUILD_BYPRODUCTS ${STAGED_INSTALL_PREFIX}/include/stb
    DOWNLOAD_NO_PROGRESS ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    LOG_INSTALL ON
)