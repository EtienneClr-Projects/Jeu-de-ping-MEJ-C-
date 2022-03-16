cmake_minimum_required(VERSION 3.21)
project(JeuDePingMEJ)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")


set(SOURCE_FILES main.cpp)
add_executable(JeuDePingMEJ main.cpp Ping.cpp Ping.h TABLEAU.cpp TABLEAU.h Node.cpp Node.h)
