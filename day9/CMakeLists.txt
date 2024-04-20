cmake_minimum_required(VERSION 3.0)
project(CppServerDay9)

set(CMAKE_CXX_STANDARD 11)

include_directories("include")

file(GLOB SOURCES "src/*.cpp")

add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)