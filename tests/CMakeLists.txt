cmake_minimum_required(VERSION 3.20)

project(testing)

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/googletest/googletest/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include/)

add_subdirectory(unit)
