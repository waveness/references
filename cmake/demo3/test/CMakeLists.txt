cmake_minimum_required(VERSION 2.8)
project(mytest)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)
add_executable(unit_test
    main.cpp)
target_link_libraries(unit_test
    demo
    mylib
    )

message(STATUS "[test]==>PROJECT_BINARY_DIR= " ${PROJECT_BINARY_DIR})
message(STATUS "[test]==>PROJECT_SOURCE_DIR= " ${PROJECT_SOURCE_DIR})

message(STATUS "[test]==>CMAKE_CUR_SRC_DIR= " ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "[test]==>CMAKE_CUR_BIN_DIR= " ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "[test]==>SRC_PREFIX= " ${SRC_PREFIX})

message(STATUS "[test]==>CMAKE_SRC_DIR= " ${CMAKE_SOURCE_DIR})
message(STATUS "[test]==>CMAKE_BIN_DIR= " ${CMAKE_BINARY_DIR})
enable_testing()
#add_test(NAME runtest COMMAND ${PROJECT_BINARY_DIR}/test/unit_test)
add_test(NAME runtest COMMAND ${PROJECT_SOURCE_DIR}/output/bin/unit_test)

