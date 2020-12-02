
cmake_minimum_required(VERSION 3.8)
project(FM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fopenmp")

include_directories(include)

add_executable(FM src/main.cpp src/math_lib.cpp src/factory.cpp src/operators.cpp)

#target_link_libraries(IO ${LIBS})
