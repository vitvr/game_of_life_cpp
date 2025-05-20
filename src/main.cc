#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <stdexcept>
#include <string>

#include "matrix.h"

int main()
{
    std::ifstream file("gosper_glider_gun.rle");
    if (!file)
        throw "Could not read file";
    
    // read and verify first line (header)
    std::regex r(R"(x\s*=\s*([123456789]+\d*),\s*y\s*=\s*([123456789]+\d*))");
    std::smatch m;
    std::string line;
    std::getline(file, line);
    std::regex_match(line, m, r);

    if (m.empty())
        throw std::runtime_error{"File does not match .rle format"};

    // extract grid dimensions from header
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
    
    // std::cout << '\n' << *m[1].first << '\n' << '\n';

    for (auto s : m)
        std::cout << s << '\n';

    std::cout << '\n';

    std::vector<bool> grid(rows * columns);

    // extract each row in the rle
    // r.assign(R"((?:((?:\d*[bo]\s*)+\$)\s*))");
    r.assign(R"((?:((?:\d*[bo]\s*)+)[\$\!]\s*))");
    for (auto row_iter = std::sregex_iterator(rle.begin(), rle.end(), r); row_iter != std::sregex_iterator {}; row_iter = std::next(row_iter))
    {
        std::string row = (*row_iter)[0];
        // remove end of row/pattern character ($ or !)
        row.pop_back();
        std::cout << row << '\n';
        
        // extract each pair <run_count><tag> in the row
        std::regex r_pair(R"(\d+[bo]|[bo])");
        for (auto pair_iter = std::sregex_iterator(row.begin(), row.end(), r_pair); pair_iter != std::sregex_iterator {}; pair_iter = std::next(pair_iter))
        {
            // extract <run_count> <tag> separately (into m[1] and m[2] respectively)
            std::string pair = (*pair_iter)[0];
            std::regex r_pair_separate(R"((\d+)*([bo]))");
            std::regex_match(pair, m, r_pair_separate);

            std::cout << '\n';
            std::cout << (*pair_iter)[0] << '\n';

            int run_count;
            bool tag; // bool unless support for more than 2 states is added

            if (m[1].matched)
                run_count = std::stoi(m[1]);
            else
                run_count = 1;

            if (m[2] == 'b')
                tag = false;
            else
                tag = true;

            grid.insert(grid.end(), run_count, tag);
            
            std::cout << '\n';
            std::cout << m[2];
            std::cout << '\n';
        }
    }
    
    // Matrix<bool> matrix(rows, columns, grid);

    return 0;
}
