cmake_minimum_required(VERSION 3.6.3)
project(kvssignaling C)

option(SIGNALING_DO_NOT_USE_CUSTOM_CONFIG "Do not have custom signaling config file" OFF)
message(STATUS "SIGNALING_DO_NOT_USE_CUSTOM_CONFIG is ${SIGNALING_DO_NOT_USE_CUSTOM_CONFIG}")

find_library(COREJSON_LIBRARY NAMES corejson ${coreJSON} REQUIRED)

include(signalingFilePaths.cmake)

if(BUILD_SHARED_LIBS)
    add_library(kvssignaling SHARED ${SIGNALING_SOURCES})
else()
    add_library(kvssignaling STATIC ${SIGNALING_SOURCES})
endif()

if(SIGNALING_DO_NOT_USE_CUSTOM_CONFIG)
    target_compile_definitions( kvssignaling PUBLIC SIGNALING_DO_NOT_USE_CUSTOM_CONFIG )
endif(SIGNALING_DO_NOT_USE_CUSTOM_CONFIG)

target_include_directories(kvssignaling PUBLIC
                           ${SIGNALING_INCLUDE_PUBLIC_DIRS}
                           ${COREJSON_INCLUDE_DIRS})

set_target_properties(kvssignaling PROPERTIES
                      INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}"
                      INSTALL_RPATH_USE_LINK_PATH TRUE)
target_link_libraries(kvssignaling PRIVATE ${COREJSON_LIBRARY})

# install header files
install(
    FILES ${SIGNALING_INCLUDE_PUBLIC_FILES}
    DESTINATION include/kvssignaling)

install(
    TARGETS kvssignaling
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
