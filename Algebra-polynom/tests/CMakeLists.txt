project(tests)

set(CMAKE_CXX_STANDARD 17)

set(SRC_LIST Tests.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})