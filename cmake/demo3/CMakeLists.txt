cmake_minimum_required(VERSION 3.0)

include(cmake/internal_utils.cmake)
project(demo3)

set(CMAKE_CXX_STANDARD 11)
if (${platform} STREQUAL "linux")
  set(CMAKE_CXX_FLAGS "-Wall -Werror")
endif()
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/output)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/mylib
    )

message(STATUS "[demo]===>CMAKE_CURRENT_SOURCE_DIR=" ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "[demo]===>CMAKE_CURRENT_Binary_DIR=" ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "[demo]===>PROJECT_BINARY_DIR      =" ${PROJECT_BINARY_DIR})
message(STATUS "[demo]===>PROJECT_SOURCE_DIR      =" ${PROJECT_SOURCE_DIR})
message(STATUS "[demo]===>CMAKE_BINARY_DIR        =" ${CMAKE_BINARY_DIR})
message(STATUS "[demo]===>CMAKE_SOURCE_DIR        =" ${CMAKE_SOURCE_DIR})
message(STATUS "[demo]===>ProjectName_BINARY_DIR  =" ${demo3_BINARY_DIR})
message(STATUS "[demo]===>ProjectName_SOURCE_DIR  =" ${demo3_SOURCE_DIR})


link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/
    )

set(SRC_PREFIX src)
#set(SOURCE_FILES
#    ${SRC_PREFIX}/module1.cpp
#    ${SRC_PREFIX}/module2.cpp
#    ${SRC_PREFIX}/manager.cpp
#    )
aux_source_directory(${SRC_PREFIX} SOURCE_FILES)

file(GLOB INCS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
source_group("include" FILES ${INCS})

source_group("src" FILES ${SOURCE_FILES})

#test foreach
foreach(val 1 5 1)
    message(STATUS "val-->" ${val})
endforeach(val)

foreach(val RANGE 1 5 1)
    message(STATUS "val-->" ${val})
endforeach(val)
#test function
test_function("arg1" "arg2")
#test macro
macro(PRINT msg level)
    message(${level} ${msg} )
endmacro(PRINT)
PRINT("hello macro ^_^" "STATUS")

option(FOO_ENABLE "Enable VERSION" ON)
if(FOO_ENABLE)
    message(STATUS "FOO_ENABLED")
endif(FOO_ENABLE)

set(DEMO_VERSION_MAJOR 1)
set(DEMO_VERSION_MINOR 0)
configure_file(config.h.in ${PROJECT_SOURCE_DIR}/config.h @ONLY)

add_definitions(-DTEST_CMAKE_DEFINE)

add_subdirectory(${PROJECT_SOURCE_DIR}/mylib)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/linux_x86
)

add_library(demo STATIC ${SOURCE_FILES} ${INCS})
target_link_libraries(demo mylib)

add_dependencies(demo copyheader)
#get_target_property(LIB_LOC demo LOCATION)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
#add_custom_command(
#    TARGET demo
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND}
#    ARGS -E copy ${PROJECT_BINARY_DIR}/libdemo.so /home/czb/Downloads)

set(GEN_HEADER "config.h")
add_custom_command(
    OUTPUT ${GEN_HEADER}
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${PROJECT_SOURCE_DIR}/config.h ${PROJECT_SOURCE_DIR}/include/
    COMMENT "run copy")
add_custom_target(
    copyheader ALL DEPENDS ${GEN_HEADER})

#install DESTINATION FILES
if (${platform} STREQUAL "win")
    install(TARGETS demo
            ARCHIVE DESTINATION lib)
else()
    install(TARGETS demo ARCHIVE DESTINATION lib)
endif()
install(FILES ${PROJECT_SOURCE_DIR}/include/manager.h DESTINATION include)
#execute_process(COMMAND adb RESULT_VARIABLE result OUTPUT_VARIABLE output)
#message(STATUS "${result}")
#message(STATUS "${output}")
