# vim: et ts=4 sts=4 sw=4 tw=0

message (STATUS, "====>${PROJECT_SOURCE_DIR}")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src/wrapper_jsoncpp
)

ADD_EXECUTABLE( wrapper_test 
                wrapper_jsoncpp.cpp
                wrapper_jsoncpp.h
                main.cpp
                )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS( -DJSON_DLL )
    TARGET_LINK_LIBRARIES(wrapper_test jsoncpp_lib)
ELSE(BUILD_SHARED_LIBS)
    TARGET_LINK_LIBRARIES(wrapper_test jsoncpp_lib_static)
ENDIF()

# another way to solve issue #90
#set_target_properties(jsoncpp_test PROPERTIES COMPILE_FLAGS -ffloat-store)
