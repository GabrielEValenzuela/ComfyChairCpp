<<<<<<< HEAD
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(
  "ComfyChairCpp"
=======
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(
  "ComfyChairC++"
>>>>>>> master
  VERSION 1.0.0
  DESCRIPTION "A comprehensive system designed to streamline the management of scientific conferences"
  LANGUAGES CXX
)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers files
include_directories(include)

include(FetchContent)
set(GTEST_GIT_URL "https://github.com/google/googletest.git") # Download gtest from github
set(NLOHMANN_JSON_GIT_URL "https://github.com/nlohmann/json.git") # Download nlohmann/json from github

set(FETCHCONTENT_QUIET OFF)

# FetchContent_Declare is a CMake function that downloads the content of a git repository
# and stores it in the build directory.
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY ${NLOHMANN_JSON_GIT_URL}
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann_json
  GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(nlohmann_json)

# Add sources files
file(GLOB COMFY_CHAIR_SRC
    "src/*.cpp"
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann_json/include)

add_executable(${PROJECT_NAME} ${COMFY_CHAIR_SRC})


# To run testing and coverage, run cmake with -DRUN_COVERAGE=1
if (RUN_COVERAGE EQUAL 1)

  FetchContent_Declare(
  googletest
  GIT_REPOSITORY ${GTEST_GIT_URL}
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest
  GIT_TAG v1.14.0  # Optionally pin to a stable release
  )

  FetchContent_MakeAvailable(googletest)

  add_subdirectory(tests)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -O3)
endif()
