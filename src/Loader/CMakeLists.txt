cmake_minimum_required(VERSION 3.14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(fsloader
    DecodedStream.cpp
    FilePath.cpp
    LoadError.cpp
    Loadable.cpp
    LoaderLink.cpp
    LoaderSupport.cpp
    Logging.cpp
    LoggingLoadable.cpp
    RunFileArchiveDirector.cpp
    TokenStream.cpp)
target_link_libraries(fsloader
        PUBLIC
        log4cplus::log4cplus
        mitre::cppuom)
target_include_directories(fsloader PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${LOG4CPLUS_DIRS}
)
set_target_properties(fsloader PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
if (NOT BUILD_SHARED_LIBS)
        target_compile_definitions(fsloader PUBLIC LOG4CPLUS_STATIC)
endif ()
add_library(mitre::fsloader ALIAS fsloader)
