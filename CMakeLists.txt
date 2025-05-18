cmake_minimum_required(VERSION 3.24)
project(game_of_life_cpp
    VERSION 0.1
    DESCRIPTION "Conway's Game of Life in C++"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(test)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/571930618fa96eabcd05b573285edbee9fc13bae.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)
