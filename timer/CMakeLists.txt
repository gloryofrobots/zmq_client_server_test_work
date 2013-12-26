set(MY_LIB_NAME timer)

find_package(Boost 1.47 COMPONENTS date_time  REQUIRED)

set(LIB_SRC_LIST 
    "Timer.h"
    "TimerBoost.h"
    "TimerBoost.cpp"
 )

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

ADD_LIBRARY( ${MY_LIB_NAME} ${LIB_SRC_LIST} )
TARGET_LINK_LIBRARIES (${MY_LIB_NAME}  ${Boost_LIBRARIES})
