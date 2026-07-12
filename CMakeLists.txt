cmake_minimum_required(VERSION 3.20)

project(root_finder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS headers)

add_library(newton INTERFACE)
target_include_directories(newton
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(newton
    INTERFACE
        Eigen3::Eigen
)

add_library(bisection INTERFACE)
target_include_directories(bisection
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(bisection
    INTERFACE
        Boost::headers
)

