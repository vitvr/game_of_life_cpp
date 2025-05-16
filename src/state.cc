#include "state.h"

#include <fstream>
#include <iostream>
#include <vector>

State::State(std::string file_name, char dead, char alive) : grid_ {ReadSeedFile(file_name, dead, alive)} {}

State::State(std::vector<std::vector<bool>> grid) : grid_ {grid} {}

std::vector<std::vector<bool>> State::ReadSeedFile(std::string file_name, char dead, char alive)
{
    std::ifstream seed(file_name);
    
    std::string line;

    std::vector<std::vector<bool>> grid;

    for (int i; seed >> line;)
    {
        std::cout << line << '\n';
        std::vector<bool> row;
        for (char cell : line)
        {
            if (cell == dead)
                row.push_back(false);
            else if (cell == alive)
                row.push_back(true);
        }
        grid.push_back(row);
    }

    std::cout << "here\n";

    return grid;
}
