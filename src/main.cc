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

    return 0;
}
