project(server_project)

cmake_minimum_required(VERSION 2.8)

set(SRC_LIST 
    ${SRC_LIST}
    "main.cpp"
    "Server.cpp"
    "Server.h"
    "ServerZMQ.cpp"
    "ServerZMQ.h"
    )

   set(LIB_DIR 
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )
    
add_executable(server ${SRC_LIST})

add_subdirectory(${LIB_DIR}/cppjson cppjson)
include_directories ("${LIB_DIR}/cppjson")
set (EXTRA_LIBS ${EXTRA_LIBS} cppjson)
SET_TARGET_PROPERTIES(cppjson PROPERTIES LINKER_LANGUAGE C)

target_link_libraries (server  ${EXTRA_LIBS})
