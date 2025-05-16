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
    // std::vector<std::vector<bool>> grid = {
    //     {false, true, false},
    //     {false, true, false},
    //     {false, true, false}
    // };

    // State a(grid);

    // for (std::vector<bool> row : ReadSeedFile("in.txt", '.', '#'))
    // {
    //     for (bool cell : row)
    //         std::cout << cell;
    //     std::cout << '\n';
    // }

    return 0;
}
