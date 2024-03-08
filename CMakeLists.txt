cmake_minimum_required(VERSION 3.6.3)
project(kvssignaling C)

find_library(COREJSON_LIBRARY corejson REQUIRED)

include(signalingFilePaths.cmake)

add_library(kvssignaling ${SIGNALING_SOURCES})

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
