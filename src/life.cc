#include <fstream>
// #include <iostream>
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
    std::ifstream ifs(address);

    

    std::vector<std::vector<bool>> grid;

    return grid;
}

int main()
{
    std::vector<std::vector<bool>> grid = {
        {false, true, false},
        {false, true, false},
        {false, true, false}
    };

    State a(grid);

    return 0;
}
