cmake_minimum_required(VERSION 3.20)
project(root_finder LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

## INSERT NEW find_package HERE ##

add_library(root_finder INTERFACE)
target_include_directories(root_finder
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(root_finder
    INTERFACE
        Eigen3::Eigen
)

## INSERT NEW LINK LIBRARY HERE ##

enable_testing()
add_executable(root_finder_tests
    tests/test_newton.cpp
)
target_link_libraries(root_finder_tests
    PRIVATE
        Catch2::Catch2WithMain
        root_finder
)

## INSERT NEW TEST FILE HERE ##

include(CTest)
include(Catch)
catch_discover_tests(root_finder_tests)
