cmake_minimum_required(VERSION 3.0)
project(CppServerDay3)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(server src/server.cpp src/utils.cpp)
add_executable(client src/client.cpp src/utils.cpp)