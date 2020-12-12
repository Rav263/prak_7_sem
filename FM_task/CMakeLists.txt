
cmake_minimum_required(VERSION 3.8)
project(FM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp")

include_directories(
    include
    ${GTEST_INCLUDE_DIRS}
    )

add_executable(FM src/main.cpp src/math_lib.cpp src/factory.cpp src/operators.cpp src/gradient_descent.cpp)
target_link_libraries(FM ${GTEST_LIBRARIES} ${LIBS})

add_executable(TestFM src/test.cpp src/math_lib.cpp src/factory.cpp src/operators.cpp src/gradient_descent.cpp)
target_link_libraries(TestFM ${GTEST_LIBRARIES} ${LIBS})
enable_testing()
add_test(TestFM "./TestFM")
