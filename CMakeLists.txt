cmake_minimum_required(VERSION 3.20)

project(root_finder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)

add_library(newton INTERFACE)
target_include_directories(newton INTERFACE include)
target_link_libraries(newton INTERFACE Eigen3::Eigen)


add_library(bisection INTERFACE)
target_include_directories(bisection INTERFACE include)
target_link_libraries(bisection INTERFACE Boost::boost)


add_executable(test_newton tests/test_newton.cpp)
target_link_libraries(test_newton PRIVATE newton)


add_executable(test_bisection tests/test_bisection.cpp)
target_link_libraries(test_bisection PRIVATE bisection)
