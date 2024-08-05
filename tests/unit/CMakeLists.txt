cmake_minimum_required(VERSION 3.20)

project(comfy_chair_unit_tests)

file(GLOB PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*[!main]*.cpp
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage -fsanitize=address,leak,undefined")

include_directories(${CMAKE_SOURCE_DIR}/tests/mocks)

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
