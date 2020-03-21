project(tests)

set(CMAKE_CXX_STANDARD 17)

set(SRC_LIST Tests.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})