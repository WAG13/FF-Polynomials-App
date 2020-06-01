cmake_minimum_required(VERSION 3.14)
project(Algebra-polynom)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build tests" ON)

add_executable(main main.cpp utils.cpp Polynom/Polynom.cpp Matrix/Matrix.cpp)
target_include_directories(main PRIVATE ./)

if (BUILD_TESTS)
    add_executable(tests Test/Test.cpp utils.cpp Polynom/Polynom.cpp Matrix/Matrix.cpp)
    target_include_directories(tests PRIVATE ./)
endif()
