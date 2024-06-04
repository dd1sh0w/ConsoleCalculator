cmake_minimum_required(VERSION 3.27)
project(ConsoleCalculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConsoleCalculator main.cpp
        functions/functions.cpp
        functions/functions.h)
