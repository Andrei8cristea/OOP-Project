cmake_minimum_required(VERSION 3.30)
project(proiect1)

set(CMAKE_CXX_STANDARD 20)

add_executable(proiect1 main.cpp
        Movie.cpp
        Movie.h
        MovieDate.cpp
        MovieDate.h
        Room.cpp
        Room.h)
