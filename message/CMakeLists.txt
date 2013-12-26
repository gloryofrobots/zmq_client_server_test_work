set(MY_LIB_NAME message)
set(LIB_SRC_LIST 
    "Message.h"
    "MessageProvider.h"
    "MessageProviderJson.cpp"
    "MessageProviderJson.h"
 )

INCLUDE_DIRECTORIES("${LIB_DIR}/common")
INCLUDE_DIRECTORIES("${LIB_DIR}/cppjson")
ADD_LIBRARY( ${MY_LIB_NAME} ${LIB_SRC_LIST} )
TARGET_LINK_LIBRARIES (${MY_LIB_NAME}  cppjson)
