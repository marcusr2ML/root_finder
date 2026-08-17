#Python Boost ABI error demo
cmake_minimum_required(VERSION 3.15)

project(python_boost_ABI LANGUAGES CXX )


find_package(Python 3.14 EXACT COMPONENTS Interpreter Development REQUIRED)
find_package(Boost REQUIRED COMPONENTS python)

execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_library(mymodule MODULE mymodule2.cpp)

target_include_directories(mymodule PRIVATE ${Python_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR})
target_link_libraries(mymodule PRIVATE ${Python_LIBRARIES} ${Boost_LIBRARIES})

set_target_properties(mymodule PROPERTIES
    PREFIX ""
    OUTPUT_NAME "abi_result"
    SUFFIX ".so"
)

