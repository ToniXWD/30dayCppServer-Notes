cmake_minimum_required(VERSION 3.0)
project(CppServerDay7)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(server ${SOURCES} server.cpp)
add_executable(client client.cpp src/util.cpp)