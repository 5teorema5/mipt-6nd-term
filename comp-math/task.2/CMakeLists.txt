cmake_minimum_required(VERSION 3.10)
project(theRiemanProblem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        main.cpp
        algebra.cpp
        algebra.h
        )

add_executable(app ${SOURCES})