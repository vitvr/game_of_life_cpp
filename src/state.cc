#include "state.h"

// #include <fstream>
// #include <iostream>
// #include <vector>

State::State(Matrix<bool> grid) : grid_ {grid}, y_offset_ {-int ((grid.Rows() - 1) / 2)}, x_offset_ {-int ((grid.Columns() - 1) / 2)} {}

Matrix<bool> State::GetMatrix() { return grid_; }

int State::YOffset() { return y_offset_; }

int State::XOffset() { return x_offset_; }

// State::State(std::string file_name, char dead, char alive) : grid_ {ReadSeedFile(file_name, dead, alive)} {}

// std::vector<std::vector<bool>> State::ReadSeedFile(std::string file_name, char dead, char alive)
// {
//     std::ifstream seed(file_name);
//     std::string line;
//     std::vector<std::vector<bool>> grid;

//     for (int i; seed >> line;)
//     {
//         std::cout << line << '\n';
//         std::vector<bool> row;
//         for (char cell : line)
//         {
//             if (cell == dead)
//                 row.push_back(false);
//             else if (cell == alive)
//                 row.push_back(true);
//         }
//         grid.push_back(row);
//     }

//     return grid;
// }
