cmake_minimum_required(VERSION 3.12.4)

project(comfy_chair_unit_tests)

set(CMAKE_CXX_FLAGS_DEBUG "-g --coverage -fsanitize=address,leak,undefined")

file(GLOB PROJECT_SOURCES
    *.cpp
    ${CMAKE_SOURCE_DIR}/src/*[!main]*.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME}
    debug gtestd
    debug gmockd
    debug gtest_maind
    debug gmock_maind
    optimized gtest
    optimized gmock
    optimized gtest_main
    optimized gmock_main
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
