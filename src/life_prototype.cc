#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> step(const vector<vector<bool>>& state)
{
    int iter = 0;
    vector<vector<bool>> new_state(
        state.size(),
        vector<bool>(state[0].size()));
    for (int i = 0; i < state.size(); ++i)
    {
        for (int j = 0; j < state[0].size(); ++j)
        {
            int neighbors = 0;

            // up
            if (i != 0)
                neighbors += state[i - 1][j];
            // down
            if (i != state.size() - 1)
                neighbors += state[i + 1][j];
            // left
            if (j != 0)
                neighbors += state[i][j - 1];
            // right
            if (j != state[0].size() - 1)
                neighbors += state[i][j + 1];
            // up left
            if (i != 0 && j != 0)
                neighbors += state[i - 1][j - 1];
            // down left
            if (i != state.size() - 1  && j != 0)
                neighbors += state[i + 1][j - 1];
            // up right
            if (i != 0 && j != state[0].size() - 1)
                neighbors += state[i - 1][j + 1];
            // down right
            if (i != state.size() - 1  && j != state[0].size() - 1)
                neighbors += state[i + 1][j + 1];

            if (state[i][j] == true)
            {
                if (neighbors != 2 && neighbors != 3)
                    new_state[i][j] = false;
                else
                    new_state[i][j] = true;
            }
            else
            {
                if (neighbors == 3)
                    new_state[i][j] = true;
            }
        }
    }
    
    return new_state;
}

int main()
{

    vector<vector<bool>> state = {
        {false, false, false, false},
        {false, true, true, true},
        {true, true, true, false},
        {false, false, false, false}
    };

    // vector<vector<bool>> state = {
    //     { false, false, false},
    //     { true, true, true},
    //     { false, false, false}
    // };

    for (auto l : state)
    {
        for (auto e : l)
            std::cout << e;
        std::cout << '\n';
    }

    std::cout << '\n';

    auto new_state = step(state);

    for (auto l : new_state)
    {
        for (auto e : l)
            std::cout << e;
        std::cout << '\n';
    }
    std::cout << '\n';

    new_state = step(new_state);

    for (auto l : new_state)
    {
        for (auto e : l)
            std::cout << e;
        std::cout << '\n';
    }

    return 0;
}
