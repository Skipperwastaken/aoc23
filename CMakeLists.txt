cmake_minimum_required(VERSION 3.26)
project(aoc23)

set(CMAKE_CXX_STANDARD 23)

add_executable(aoc23 main.cpp
        solution1_1.h
        solution1_2.h
        solution2_1.h
        solution2_2.h
        solution3_1.h
        solution3_2.h
        solution4_1.h
        solution4_2.h
        solution5_1.h
        solution5_2.h
        solution6_1.h
        solution6_2.h
        solution7_1.h
        solution7_2.h
        solution8_1.h
        solution8_2.h
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/inputs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

