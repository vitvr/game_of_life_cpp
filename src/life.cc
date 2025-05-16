#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "state.h"

class Game
{
    public:
        State GetNext();
        State GetPrevious();
    private:
        std::vector<State> states_;

};

std::vector<std::vector<bool>> ReadSeedFile(std::string address, char dead, char alive)
{
    std::ifstream seed(address);
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

int main()
{
    // std::vector<std::vector<bool>> grid = {
    //     {false, true, false},
    //     {false, true, false},
    //     {false, true, false}
    // };

    // State a(grid);

    for (std::vector<bool> row : ReadSeedFile("in.txt", '.', '#'))
    {
        for (bool cell : row)
            std::cout << cell;
        std::cout << '\n';
    }

    return 0;
}
