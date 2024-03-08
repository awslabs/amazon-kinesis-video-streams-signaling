cmake_minimum_required(VERSION 3.6.3)
project(kvssignaling C)

find_library(COREJSON_LIBRARY coreJSON)

message("LIB_COREJSON: " ${LIB_COREJSON})

if(COREJSON_LIBRARY)
	message(STATUS "coreJSON found")
else()
    message(STATUS "coreJSON not found")

    include(source/dependency/coreJSON/jsonFilePaths.cmake)
    add_library(coreJSON ${JSON_SOURCES})
    message(STATUS "JSON_SOURCES: ${JSON_SOURCES}")

    target_include_directories(coreJSON PUBLIC
                               ${JSON_INCLUDE_PUBLIC_DIRS})

    # install header files
    install(
        FILES ${JSON_INCLUDE_PUBLIC_DIRS}/core_json.h
        DESTINATION include/corejson)
    
    install(
        TARGETS coreJSON
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif()

include(signalingFilePaths.cmake)

add_library(kvssignaling ${SIGNALING_SOURCES})

target_include_directories(kvssignaling PUBLIC
                           ${SIGNALING_INCLUDE_PUBLIC_DIRS})

target_link_libraries(kvssignaling coreJSON)

# install header files
install(
    FILES ${SIGNALING_INCLUDE_PUBLIC_FILES}
    DESTINATION include/kvssignaling)

install(
    TARGETS kvssignaling
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
