cmake_minimum_required(VERSION 3.12.4)

project(testing)

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/googletest/googletest/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include/)

link_directories(${CMAKE_SOURCE_DIR}/external/googletest/lib/)

add_subdirectory(unit)
