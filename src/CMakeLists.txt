cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(OpenGL_Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EXISTS "${STAGED_INSTALL_PREFIX}/lib64")
    set(_LIBDIR "lib64")
elseif(EXISTS "${STAGED_INSTALL_PREFIX}/lib")
    set(_LIBDIR "lib")
else()
    message(FATAL_ERROR "No 'lib' or 'lib64' directory found in ${STAGED_INSTALL_PREFIX}")
endif()

file(TO_NATIVE_PATH "${STAGED_INSTALL_PREFIX}/${_LIBDIR}/cmake/glfw3" glfw3_DIR)
# file(TO_NATIVE_PATH "${STAGED_INSTALL_PREFIX}/${_LIBDIR}/cmake/glew" GLEW_DIR)

message(STATUS "glfw3_DIR is... ${glfw3_DIR}")
# message(STATUS "GLEW_DIR is... ${GLEW_DIR}")

find_package(glfw3 REQUIRED CONFIG)

# set(GLEW_USE_STATIC_LIBS ON)
# find_package(GLEW REQUIRED CONFIG)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib/glad ${CMAKE_BINARY_DIR}/glad_build)

# set(SRCS main.cpp)
file(GLOB_RECURSE SRCS
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

if(APPLE)
    # create bundle on apple compiles
    add_executable(main MACOSX_BUNDLE ${SRCS})    
    
    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)

    # Copy res/ folder into the bundle's Resources directory
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/../res"
        "$<TARGET_BUNDLE_CONTENT_DIR:main>/Resources/res"
    )
else()
    # No WIN32! We don't want WinMain() with GLFW.
    add_executable(main ${SRCS} main.exe.manifest)
endif()

target_link_libraries(main PRIVATE glad glfw)

set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})