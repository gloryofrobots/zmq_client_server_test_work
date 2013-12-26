project(client_project)
cmake_minimum_required(VERSION 2.8)



FIND_PACKAGE(Qt4 REQUIRED)

SET(dep_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
FIND_PACKAGE(dep REQUIRED)


QT4_WRAP_CPP(client_HEADERS_MOC ${client_HEADERS})
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(LIB_DIR 
"${CMAKE_CURRENT_SOURCE_DIR}/.."
)
    
add_executable(client ${client_SOURCES} ${client_HEADERS_MOC})

add_subdirectory(${LIB_DIR}/cppjson cppjson)
include_directories ("${LIB_DIR}/cppjson" ${CMAKE_CURRENT_BINARY_DIR})

SET_TARGET_PROPERTIES(cppjson PROPERTIES LINKER_LANGUAGE C)
set (EXTRA_LIBS ${EXTRA_LIBS} cppjson ${QT_LIBRARIES})

target_link_libraries (client  ${EXTRA_LIBS})
