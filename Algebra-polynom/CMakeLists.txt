cmake_minimum_required(VERSION 3.12)
project(Algebra-polynom)

set(CMAKE_CXX_STANDARD 17)

set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/Algebra-polynom)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${SRC_DIR})

set(LIB_NAME ${PROJECT_NAME}core)
add_library(${LIB_NAME} STATIC Algebra-polynom/Polynom.cpp Algebra-polynom/Matrix.cpp)

option(ENABLE_TESTS "Build tests for project" ON)
if(ENABLE_TESTS)
    add_subdirectory(${TESTS_DIR})
endif()

add_executable(main Algebra-polynom/Source.cpp Algebra-polynom/Polynom.cpp Algebra-polynom/Matrix.cpp)