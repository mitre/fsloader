cmake_minimum_required(VERSION 3.15)
project(fsloader VERSION 1.0 LANGUAGES CXX)

option(BUILD_EXAMPLE "Build the cppuom example executable" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Get CPM
include(${PROJECT_SOURCE_DIR}/.cmake/get_cpm.cmake)

CPMAddPackage(
    NAME cppuom
    GIT_REPOSITORY https://github.com/mitre/cppuom.git
    GIT_TAG 2.2
)
if (cppuom_ADDED)
    message(STATUS "cppuom added by CPM: ${cppuom_SOURCE_DIR}")
else ()
    message (ERROR "cppuom not added by CPM, cannot continue")
endif ()

CPMAddPackage(
    NAME log4cplus
    GITHUB_REPOSITORY log4cplus/log4cplus
    GIT_TAG REL_2_1_2
    OPTIONS
     "BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS}"
     "LOG4CPLUS_BUILD_TESTING FALSE"
     "LOG4CPLUS_BUILD_LOGGINGSERVER FALSE"
)
if (log4cplus_ADDED)
    message(STATUS "log4cplus added by CPM: ${log4cplus_SOURCE_DIR}")
    set (LOG4CPLUS_DIRS 
        ${log4cplus_BINARY_DIR}/include
        ${log4cplus_SOURCE_DIR}/include)
else ()
    message (ERROR "log4cplus not added by CPM, cannot continue")
endif ()

add_subdirectory(src/Loader)

if (BUILD_EXAMPLE)
    add_executable(example example.cpp)
    target_link_libraries(example PRIVATE mitre::fsloader)
    set_target_properties(example PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    )
endif ()
