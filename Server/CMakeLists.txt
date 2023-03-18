cmake_minimum_required(VERSION 3.20)

project(server)

include_directories(../)

add_executable(s ./Server.cpp ./server.cpp)