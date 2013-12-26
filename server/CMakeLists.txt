project(server_project)

cmake_minimum_required(VERSION 2.8)

set(LIB_DIR 
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    )

SET(dep_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

FIND_PACKAGE(dep REQUIRED)

#message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
#message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
#message(status "** Boost Libraries: ${Boost_LIBRARIES}")

find_package(Boost 1.47 COMPONENTS date_time REQUIRED)

IF(NOT DEP_FOUND)
    MESSAGE(FATAL_ERROR "Dependencies not found")
ENDIF(DEP_FOUND)

INCLUDE(src.cmake)
    
ADD_EXECUTABLE(server ${SOURCES})

ADD_SUBDIRECTORY(${LIB_DIR}/cppjson cppjson)
SET_TARGET_PROPERTIES(cppjson PROPERTIES LINKER_LANGUAGE C)

ADD_SUBDIRECTORY(${LIB_DIR}/message message)

INCLUDE_DIRECTORIES("${LIB_DIR}/cppjson")
INCLUDE_DIRECTORIES("${LIB_DIR}/common")
INCLUDE_DIRECTORIES("${LIB_DIR}/zmqhelpers")
INCLUDE_DIRECTORIES("${LIB_DIR}/message")
INCLUDE_DIRECTORIES(${ZEROMQ_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
LINK_DIRECTORIES(${ZEROMQ_LIBRARY})

SET(EXTRA_LIBS ${EXTRA_LIBS} message cppjson ${ZEROMQ_LIBRARY} ${Boost_LIBRARIES})


TARGET_LINK_LIBRARIES(server  ${EXTRA_LIBS})

