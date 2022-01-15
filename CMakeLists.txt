cmake_minimum_required(VERSION 3.20)
project(TEPmax3sat)

set(CMAKE_CXX_STANDARD 11)

add_executable(TEPmax3sat main.cpp Max3SatProblem.cpp Max3SatProblem.h Optimizer.cpp Optimizer.h Individual.cpp Individual.h Random.cpp Random.h)
