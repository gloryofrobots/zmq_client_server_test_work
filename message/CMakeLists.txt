find_package(Boost 1.47 COMPONENTS date_time REQUIRED)

set(MY_LIB_NAME message)
set(LIB_SRC_LIST 
    "Message.h"
    "MessageProvider.h"
    "MessageProviderJson.cpp"
    "MessageProviderJson.h"
 )

ADD_LIBRARY( ${MY_LIB_NAME} ${LIB_SRC_LIST} )

INCLUDE_DIRECTORIES("${LIB_DIR}/cppjson")
INCLUDE_DIRECTORIES("${LIB_DIR}/common")


ADD_SUBDIRECTORY(${LIB_DIR}/cppjson cppjson)

SET_TARGET_PROPERTIES(cppjson PROPERTIES LINKER_LANGUAGE C)

TARGET_LINK_LIBRARIES(message  cppjson)
