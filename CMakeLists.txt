cmake_minimum_required(VERSION 3.14)
project(game_of_life_cpp
    VERSION 0.1
    DESCRIPTION "Conway's Game of Life in C++"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(test)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest.git
)
FetchContent_MakeAvailable(googletest)
