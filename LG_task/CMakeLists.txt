cmake_minimum_required(VERSION 3.8)
project(LG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O5 -fopenmp")

include_directories(include)

add_executable(LG src/main.cpp src/configuration.cpp src/selection.cpp src/mutate.cpp src/crossbreeding.cpp src/genetic_algorithm.cpp) 

target_link_libraries(LG ${LIBS})
