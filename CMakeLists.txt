cmake_minimum_required(VERSION 3.19)
project(cmd_runner)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmd_runner main.cpp cmd_runner.cpp cmd_runner.h)

add_executable(test_cmd test_cmd.cpp)
target_link_libraries(cmd_runner pthread)
