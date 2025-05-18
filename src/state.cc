#include "state.h"
#include <algorithm>

// #include <fstream>
// #include <iostream>
// #include <vector>

State::State(Matrix<bool> grid) : grid_ {grid}, y_offset_ {-int ((grid.Rows() - 1) / 2)}, x_offset_ {-int ((grid.Columns() - 1) / 2)} 
{
    AddMargin();
}

Matrix<bool> State::GetMatrix() { return grid_; }

int State::YOffset() { return y_offset_; }

int State::XOffset() { return x_offset_; }

void State::AddMargin()
{
    std::vector<bool> v = grid_.GetRow(0);
    // if row is has a living cell
    if (std::find(v.begin(), v.end(), true) != v.end())
    {
        --y_offset_;
        grid_.InsertRow(0, std::vector<bool>(grid_.Columns()));
    }

    v = grid_.GetColumn(0);
    if (std::find(v.begin(), v.end(), true) != v.end())
    {
        --x_offset_;
        grid_.InsertColumn(0, std::vector<bool>(grid_.Rows()));
    }

    v = grid_.GetRow(grid_.Rows() - 1);
    if (std::find(v.begin(), v.end(), true) != v.end())
        grid_.InsertRow(grid_.Rows(), std::vector<bool>(grid_.Columns()));

    v = grid_.GetRow(grid_.Columns() - 1);
    if (std::find(v.begin(), v.end(), true) != v.end())
        grid_.InsertColumn(grid_.Columns(), std::vector<bool>(grid_.Rows()));
}

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
