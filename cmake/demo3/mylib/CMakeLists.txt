cmake_minimum_required(VERSION 3.0)
project(mylib)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    )
message(STATUS "[mylib]===>CMAKE_CURRENT_SOURCE_DIR=" ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "[mylib]===>CMAKE_CURRENT_Binary_DIR=" ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "[mylib]===>PROJECT_BINARY_DIR      =" ${PROJECT_BINARY_DIR})
message(STATUS "[mylib]===>PROJECT_SOURCE_DIR      =" ${PROJECT_SOURCE_DIR})
message(STATUS "[mylib]===>CMAKE_BINARY_DIR        =" ${CMAKE_BINARY_DIR})
message(STATUS "[mylib]===>CMAKE_SOURCE_DIR        =" ${CMAKE_SOURCE_DIR})
message(STATUS "[mylib]===>ProjectName_BINARY_DIR  =" ${demo3_BINARY_DIR})
message(STATUS "[mylib]===>ProjectName_SOURCE_DIR  =" ${demo3_SOURCE_DIR})

message(STATUS "[mylib]===>CMAKE_INSTALL_PREFIX  =" ${CMAKE_INSTALL_PREFIX})
message(STATUS "[mylib]===>SRC_PREFIX  =" ${SRC_PREFIX})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} MY_SOURCE_FILES)
add_library(mylib SHARED ${MY_SOURCE_FILES})
set_target_properties(mylib PROPERTIES VERSION 1.1 SOVERSION 4)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/mylib.h DESTINATION include)