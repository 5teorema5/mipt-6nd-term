cmake_minimum_required(VERSION 3.10)
project(theRiemanProblem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        main.cpp
        grid.cpp
        )

add_executable(app ${SOURCES})