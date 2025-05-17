#include <iostream>
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



int main()
{
    std::vector<std::vector<bool>> grid = {
        {false, true, false},
        {false, true, false},
        {false, true, false}
    };

    State a(grid);

    std::cout << "Hello, World!" << '\n';

    // read file into data structure

    // output grid
        // center data

    std::vector<std::vector<char>> screen(10, std::vector<char>(20, '.'));

    for (std::vector<char> row : screen)
    {
        for (char cell : row)
            std::cout << cell;
        std::cout << '\n';
    }

    return 0;
}
