cmake_minimum_required(VERSION 3.14)
project(Algebra-polynom)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build tests" ON)

add_executable(main main.cpp Polynom/Polynom.cpp Matrix/Matrix.cpp)

if (BUILD_TESTS)
    add_executable(tests Tests/Test.cpp Polynom/Polynom.cpp Matrix/Matrix.cpp)
endif()
