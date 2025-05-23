# Game of Life in C++

[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a cellular automaton demonstrating complex behaviours arising from a very simple [set of rules](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules).

This is a personal project to learn C++ (as well as CMake and GoogleTest).

## Build

    cmake -S . -B ./build
    cmake --build ./build

## Run

    ./build/src/life ./patterns/gosper_glider_gun.rle
