#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "matrix.h"
#include "state.h"
#include "t_display.h"

Matrix<bool> ReadRLE(std::ifstream& file)
{   
    // read and verify first line (header)
    std::regex r(R"(x\s*=\s*([123456789]+\d*),\s*y\s*=\s*([123456789]+\d*))");
    std::smatch m;
    std::string line;
    std::getline(file, line);
    std::regex_match(line, m, r);

    if (m.empty())
        throw std::runtime_error{"File does not match .rle format (invalid header)"};

    // extract grid dimensions from header
    int columns = std::stoi(m[1]);
    int rows = std::stoi(m[2]);

    // read and verify rle pattern
    r.assign(R"((?:((?:\d*[bo]\s*)+\$)\s*)*((?:\d*[bo]\s*)+!))");
    std::string rle;
    while(std::getline(file, line))
    {
        rle.append(line);
    }
    std::regex_match(rle, m, r);
    
    if (m.empty())
        throw std::runtime_error{"File does not match .rle format (invalid pattern)"};

    std::vector<bool> grid;
    grid.reserve(rows * columns);

    // extract each row in the rle
    r.assign(R"((?:((?:\d*[bo]\s*)+)[\$\!]\s*))");
    for (auto row_iter = std::sregex_iterator(rle.begin(), rle.end(), r); row_iter != std::sregex_iterator {}; row_iter = std::next(row_iter))
    {
        std::string row = (*row_iter)[0];
        // remove end of row/pattern character ($ or !)
        row.pop_back();
        
        // extract each pair <run_count><tag> in the row
        std::regex r_pair(R"(\d+[bo]|[bo])");
        // keeps track of cells added to row to fill in to full length of row in grid
        int cells_added = 0;
        for (auto pair_iter = std::sregex_iterator(row.begin(), row.end(), r_pair); pair_iter != std::sregex_iterator {}; pair_iter = std::next(pair_iter))
        {
            // extract <run_count> <tag> separately (into m[1] and m[2] respectively)
            std::string pair = (*pair_iter)[0];
            std::regex r_pair_separate(R"((\d+)*([bo]))");
            std::regex_match(pair, m, r_pair_separate);

            int run_count;
            bool tag; // bool unless support for more than 2 states is added

            if (m[1].matched)
                run_count = std::stoi(m[1]);
            else
                run_count = 1;

            cells_added += run_count;

            if (m[2] == 'b')
                tag = false;
            else
                tag = true;

            grid.insert(grid.end(), run_count, tag);
        }

        // fill in row to full length
        grid.insert(grid.end(), columns - cells_added, false);

    }

    return Matrix<bool>(rows, columns, grid.begin(), grid.end());
}

int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;

    if (argc != 2)
    {
        std::cout << "Pass path/to/input_file as an argument\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    
    if (!file)
    {
        std::cout << "Could not read file\n";
        return 1;
    }

    State s;

    try 
    {
        s = ReadRLE(file);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }
    TDisplay d(80,30);

    for (int i = 0; i != 120; ++i)
    {
        d.UpdateGame(s);
        d.Print();
        s.Step();
        std::this_thread::sleep_for(42ms);
    }

    for (int i = 0; i != 10; ++i)
    {
        d.UpdateGame(s, 'd');
        d.Print();
        std::this_thread::sleep_for(42ms);
    }

    return 0;
}
