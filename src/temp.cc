#include <fstream>
#include <iostream>
#include <string>

int main()
{
    // // int a = 0 + true;
    // bool a = bool();

    // std::cout << a << '\n';

    std::ifstream ifs("../in.txt");
    std::string a;
    while(ifs >> a)
    {
        a += '\n';
        std::cout << a;
    }
    
    return 0;
}
