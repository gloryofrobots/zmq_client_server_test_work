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

 ADD_LIBRARY( ${MY_LIB_NAME} ${LIB_SRC_LIST} )

#TARGET_LINK_LIBRARIES(${MY_LIB_NAME} Core)