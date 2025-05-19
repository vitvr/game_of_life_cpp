#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <stdexcept>
#include <string>

//

int main()
{
    std::ifstream file("gosper_glider_gun.rle");
    if (!file)
        throw "Could not read file";
    
    // read and verify first line to get dimensions
    std::regex r(R"(x\s*=\s*([123456789]+\d*),\s*y\s*=\s*([123456789]+\d*))");
    std::smatch m;
    std::string line;
    std::getline(file, line);
    std::regex_match(line, m, r);

    if (m.empty())
        throw std::runtime_error{"File does not match .rle format"};

    int columns = std::stoi(m[1]);
    int rows = std::stoi(m[2]);

    for (auto s : m)
        std::cout << s << '\n';

    // read and verify rle pattern
    r.assign(R"((?:((?:\d*[bo]\s*)+\$)\s*)*((?:\d*[bo]\s*)+!))");
    std::string rle;
    while(std::getline(file, line))
    {
        rle.append(line);
    }
    std::cout << rle << "END" << '\n';
    std::regex_match(rle, m, r);
    
    if (m.empty())
        throw std::runtime_error{"File does not match .rle format"};

    std::string last_row = m[2];
    
    // std::cout << '\n' << *m[1].first << '\n' << '\n';

    for (auto s : m)
        std::cout << s << '\n';

    // get each row in the rle (already got last row in previous step)
    r.assign(R"((?:((?:\d*[bo]\s*)+\$)\s*))");
    auto iter = std::sregex_iterator(rle.begin(), rle.end(), r);

    std::string temp;
    for (auto iter = std::sregex_iterator(rle.begin(), rle.end(), r); iter != std::sregex_iterator {}; iter = std::next(iter))
    {
        std::cout << (*iter)[0] << '\n';
    }
    

    return 0;
}
