#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // // int a = 0 + true;
    // bool a = bool();

    // std::cout << a << '\n';

    std::ifstream ifs("in.txt");
    std::vector<std::vector<bool>> m;
    std::string me;
    for(int i; ifs >> me;)
    {
        std::vector<bool> vec;
        for (char a : me)
        {
            if (a == '.')
                vec.push_back(false);
            else if (a == '#')
                vec.push_back(true);
        }
        m.push_back(vec);
    }

    for (std::vector<bool> i : m)
    {
        for (bool j : i)
            std::cout << j;
        std::cout << '\n';
    }
    
    return 0;
}
