cmake_minimum_required(VERSION 3.6.3)
project(kvssignaling C)

option(SIGNALING_DO_NOT_USE_CUSTOM_CONFIG "Do not have custom signaling config file" OFF)
message(STATUS "SIGNALING_DO_NOT_USE_CUSTOM_CONFIG is ${SIGNALING_DO_NOT_USE_CUSTOM_CONFIG}")

find_library(COREJSON_LIBRARY corejson REQUIRED)

include(signalingFilePaths.cmake)

add_library(kvssignaling ${SIGNALING_SOURCES})

if(SIGNALING_DO_NOT_USE_CUSTOM_CONFIG)
    target_compile_definitions( kvssignaling PUBLIC SIGNALING_DO_NOT_USE_CUSTOM_CONFIG )
endif(SIGNALING_DO_NOT_USE_CUSTOM_CONFIG)

target_include_directories(kvssignaling PUBLIC
                           ${SIGNALING_INCLUDE_PUBLIC_DIRS}
                           ${COREJSON_INCLUDE_DIRS})

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
