cmake_minimum_required(VERSION 3.0)

include(cmake/internal_utils.cmake)
project(demo3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/output)

include_directories(
    include
    )
message(STATUS "===>PROJECT_BINARY_DIR=" ${PROJECT_BINARY_DIR})
message(STATUS "===>PROJECT_SOURCE_DIR=" ${PROJECT_SOURCE_DIR})
message(STATUS "===>CMAKE_CURRENT_SOURCE_DIR=" ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/
    )
set(SRC_PREFIX src)
set(SOURCE_FILES
    ${SRC_PREFIX}/module1.cpp
    ${SRC_PREFIX}/module2.cpp
    ${SRC_PREFIX}/manager.cpp
    )

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
macro(print msg level)
    message(${level} ${msg} )
endmacro(print)
print("hello macro ^_^" "STATUS")

option(FOO_ENABLE "Enable VERSION" ON)
if(FOO_ENABLE)
    message(STATUS "FOO_ENABLED")
endif(FOO_ENABLE)

set(DEMO_VERSION_MAJOR 1)
set(DEMO_VERSION_MINOR 0)
configure_file(config.h.in ${PROJECT_SOURCE_DIR}/config.h @ONLY)

add_definitions(-DTEST_CMAKE_DEFINE)

if (${platform} STREQUAL "linux")
    message(STATUS "linux platform ")
    link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/linux_x86
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -pthread")
    add_library(demo SHARED ${SOURCE_FILES})
    target_link_libraries(demo hobotlog)
elseif (${platform} STREQUAL "android")
    message(STATUS "the platform is===>" ${platform})
    find_library(lib_log log)
    link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/ndk
    )
    add_library(demo SHARED ${SOURCE_FILES})
    target_link_libraries(demo
        hobotlog
        ${lib_log})
elseif (${platform} STREQUAL "win")
    message(STATUS "win platform  message")
    add_library(demo SHARED ${SOURCE_FILES})
else()
    message(FATAL_ERROR "platform `${platform}` not suppored, choose from [linux | android | win | mac]")
endif ()

set_target_properties(demo PROPERTIES VERSION 1.1 SOVERSION 4)
add_dependencies(demo copyheader)
#get_target_property(LIB_LOC demo LOCATION)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_custom_command(
    TARGET demo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${PROJECT_BINARY_DIR}/libdemo.so /home/czb/Downloads)

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
    install(TARGETS demo RUNTIME DESTINATION lib)
else()
    install(TARGETS demo LIBRARY DESTINATION lib)
endif()
install(FILES ${PROJECT_SOURCE_DIR}/include/manager.h DESTINATION include)
