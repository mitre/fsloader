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
    TokenStream.cpp
)
target_link_libraries(fsloader
    PRIVATE
        log4cplus::log4cplus
    INTERFACE
        $<INSTALL_INTERFACE:log4cplus::log4cplus>
)
target_compile_features(fsloader PUBLIC cxx_std_11)
target_include_directories(fsloader PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${cppuom_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${log4cplus_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${log4cplus_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_target_properties(fsloader PROPERTIES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
)
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(fsloader PUBLIC LOG4CPLUS_STATIC)
endif()
add_library(mitre::fsloader ALIAS fsloader)

install(
    TARGETS fsloader
    EXPORT fsloaderTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
