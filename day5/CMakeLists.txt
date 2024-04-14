cmake_minimum_required(VERSION 3.0)
project(CppServerDay4)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(server src/server.cpp src/util.cpp src/Epoll.cpp src/Socket.cpp src/InetAddress.cpp src/Channel.cpp)
add_executable(client src/client.cpp src/util.cpp  src/Epoll.cpp src/Socket.cpp src/InetAddress.cpp src/Channel.cpp)