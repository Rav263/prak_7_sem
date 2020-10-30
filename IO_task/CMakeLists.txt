
cmake_minimum_required(VERSION 3.8)
project(IO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O5 -fopenmp")

add_subdirectory(externals/tinyxml2)
set(LIBS tinyxml2)

include_directories(include)

add_executable(IO src/main.cpp src/temperature.cpp src/problem.cpp src/solution.cpp src/mutable.cpp src/io.cpp src/parallel_io.cpp src/xml_parser.cpp)

target_link_libraries(IO ${LIBS})
