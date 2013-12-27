#find_package(Boost 1.47 COMPONENTS date_time REQUIRED)
#message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
#message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
#message(status "** Boost Libraries: ${Boost_LIBRARIES}")
find_package(Boost 1.47 REQUIRED)

set(MY_LIB_NAME cppjson)
set(LIB_SRC_LIST 
 json.h 
 json/token.h
 json/exception.h
 json/object.h
 json/array.h
 json/value.h
 json/json_inline.h
 json/object_inline.h
 json/array_inline.h 
 json/value_inline.h)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ADD_LIBRARY( ${MY_LIB_NAME} ${LIB_SRC_LIST} )

#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#TARGET_LINK_LIBRARIES (${MY_LIB_NAME}   ${Boost_LIBRARIES})

