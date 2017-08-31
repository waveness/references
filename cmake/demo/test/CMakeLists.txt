cmake_minimum_required(VERSION 2.8)

add_executable(unit_test
    main.cpp)

target_link_libraries(unit_test
    demo
    )

message(STATUS "[test]==>PROJECT_BINARY_DIR= " ${PROJECT_BINARY_DIR})
message(STATUS "[test]==>SRC_PREFIX= " ${SRC_PREFIX})
enable_testing()
add_test(NAME runtest COMMAND ${PROJECT_BINARY_DIR}/test/unit_test)

