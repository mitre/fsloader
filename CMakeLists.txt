cmake_minimum_required(VERSION 3.15)
project(fsloader VERSION 1.0.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(DEFINED BUILD_EXAMPLE AND NOT DEFINED FSLOADER_BUILD_EXAMPLE)
   set(
      FSLOADER_BUILD_EXAMPLE
      "${BUILD_EXAMPLE}"
      CACHE BOOL
      "Build the fsloader example executable"
   )
endif()
option(FSLOADER_BUILD_EXAMPLE "Build the fsloader example executable" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Get CPM
include(${PROJECT_SOURCE_DIR}/.cmake/get_cpm.cmake)

if(NOT TARGET cppuom)
   cpmaddpackage(
        NAME cppuom
        GIT_REPOSITORY https://github.com/mitre/cppuom.git
        GIT_TAG 2.2
        OPTIONS
            "BUILD_EXAMPLE OFF"
            "BUILD_TESTING OFF"
   )
endif()

if(TARGET mitre::cppuom OR cppuom_ADDED)
   message(STATUS "cppuom added by CPM: ${cppuom_SOURCE_DIR}")
else()
   message(FATAL_ERROR "cppuom not added by CPM, cannot continue")
endif()

if(NOT TARGET log4cplus)
   cpmaddpackage(
        NAME log4cplus
        GITHUB_REPOSITORY log4cplus/log4cplus
        GIT_TAG REL_2_1_2
        OPTIONS
            "BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS}"
            "LOG4CPLUS_BUILD_TESTING FALSE"
            "LOG4CPLUS_BUILD_LOGGINGSERVER FALSE"
   )
endif()

if(TARGET log4cplus::log4cplus OR log4cplus_ADDED)
   message(STATUS "log4cplus added by CPM: ${log4cplus_SOURCE_DIR}")
else()
   message(FATAL_ERROR "log4cplus not added by CPM, cannot continue")
endif()

add_subdirectory(src)

if(FSLOADER_BUILD_EXAMPLE)
   add_executable(example example.cpp)
   target_link_libraries(example PRIVATE mitre::fsloader)
   target_compile_features(example PRIVATE cxx_std_11)
   set_target_properties(example PROPERTIES CXX_EXTENSIONS NO)
endif()

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
   DIRECTORY ${cppuom_SOURCE_DIR}/include/
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
   FILES_MATCHING
   PATTERN "*.h"
   PATTERN "*.i"
)

install(
   EXPORT fsloaderTargets
   NAMESPACE mitre::
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsloader
)

configure_package_config_file(
   ${PROJECT_SOURCE_DIR}/.cmake/fsloaderConfig.cmake.in
   ${PROJECT_BINARY_DIR}/fsloaderConfig.cmake
   INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsloader
   PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

write_basic_package_version_file(
   ${PROJECT_BINARY_DIR}/fsloaderConfigVersion.cmake
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion
)

install(
   FILES
      ${PROJECT_BINARY_DIR}/fsloaderConfig.cmake
      ${PROJECT_BINARY_DIR}/fsloaderConfigVersion.cmake
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsloader
)
