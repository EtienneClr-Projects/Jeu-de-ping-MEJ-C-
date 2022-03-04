cmake_minimum_required(VERSION 3.21)
project(JeuDePingMEJ)

set(CMAKE_CXX_STANDARD 14)

add_executable(JeuDePingMEJ main.cpp Ping.cpp Ping.h TABLEAU.cpp TABLEAU.h)
