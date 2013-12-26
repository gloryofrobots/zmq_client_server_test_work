
set(MY_LIB_NAME message)

#message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
#message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
#message(status "** Boost Libraries: ${Boost_LIBRARIES}")
find_package(Boost 1.47 COMPONENTS date_time REQUIRED)

set(LIB_SRC_LIST 
    "Message.h"
    "MessageProvider.h"
    "MessageProviderJson.cpp"
    "MessageProviderJson.h"
 )

INCLUDE_DIRECTORIES("${LIB_DIR}/common")
INCLUDE_DIRECTORIES("${LIB_DIR}/cppjson")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

ADD_SUBDIRECTORY(${LIB_DIR}/cppjson cppjson)
SET_TARGET_PROPERTIES(cppjson PROPERTIES LINKER_LANGUAGE C)

ADD_LIBRARY( ${MY_LIB_NAME} ${LIB_SRC_LIST} )
TARGET_LINK_LIBRARIES (${MY_LIB_NAME}  cppjson  ${Boost_LIBRARIES})
