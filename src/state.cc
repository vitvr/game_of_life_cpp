#include "state.h"
#include "matrix.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// #include <fstream>
// #include <iostream>
// #include <vector>

State::State(Matrix<bool> grid) : grid_ {grid}, y_offset_ {-int ((grid.Rows() - 1) / 2)}, x_offset_ {-int ((grid.Columns() - 1) / 2)} 
{
    // grid must be at least 2x2
    if (grid.empty())
    {
        grid_ = Matrix<bool>(2, 2);
        return;
    }

    while (grid_.Rows() == 1)
        grid_.InsertRow(1, std::vector<bool>(grid_.Columns()));

    if (grid_.Columns() == 1)
        grid_.InsertColumn(1, std::vector<bool>(grid.Rows()));

    AddMargin();
}

Matrix<bool> State::GetMatrix() { return grid_; }

int State::YOffset() { return y_offset_; }

int State::XOffset() { return x_offset_; }

int State::Rows() { return grid_.Rows(); }

int State::Columns() { return grid_.Columns(); }

void State::Step()
{
    Matrix<bool> new_grid(grid_.Rows(), grid_.Columns());

    for (int i = 1; i != Rows() - 1; i++)
    {
        for (int j = 1; j != Columns() - 1; j++)
        {
            // above
            std::vector<bool> v = grid_.GetSubRow(i - 1, j - 1, 3);
            int neighbors = std::accumulate(v.begin(), v.end(), 0);
            // beside
            neighbors += grid_.Get(i, j - 1);
            neighbors += grid_.Get(i, j + 1);
            //below
            v = grid_.GetSubRow(i + 1, j - 1, 3);
            neighbors = std::accumulate(v.begin(), v.end(), neighbors);

            if (!grid_.Get(i, j))
            {
                if (neighbors == 3)
                    new_grid.Set(i, j, true);
                continue;
            }
            
            std::cerr << neighbors << '\n';

            if (neighbors == 2 || neighbors == 3)
                new_grid.Set(i, j, true);
        }
    }
    grid_ = new_grid;
    AddMargin();
}

void State::AddMargin()
{
    std::vector<bool> v = grid_.GetRow(0);
    // if row is has a living cell
    if (std::find(v.begin(), v.end(), true) != v.end())
    {
        y_offset_ -= 2;
        grid_.InsertRow(0, std::vector<bool>(grid_.Columns()));
        grid_.InsertRow(0, std::vector<bool>(grid_.Columns()));
    }
    else
    {
        v = grid_.GetRow(1);
        if (std::find(v.begin(), v.end(), true) != v.end())
        {
            --y_offset_;
            grid_.InsertRow(0, std::vector<bool>(grid_.Columns()));
        }
    }

    v = grid_.GetColumn(0);
    if (std::find(v.begin(), v.end(), true) != v.end())
    {
        x_offset_ -= 2;
        grid_.InsertColumn(0, std::vector<bool>(grid_.Rows()));
        grid_.InsertColumn(0, std::vector<bool>(grid_.Rows()));
    }
    else
    {
        v = grid_.GetColumn(1);
        if (std::find(v.begin(), v.end(), true) != v.end())
        {
            --x_offset_;
            grid_.InsertColumn(0, std::vector<bool>(grid_.Rows()));
        }
    }

    v = grid_.GetRow(grid_.Rows() - 1);
    if (std::find(v.begin(), v.end(), true) != v.end())
    {
        grid_.InsertRow(grid_.Rows(), std::vector<bool>(grid_.Columns()));
        grid_.InsertRow(grid_.Rows(), std::vector<bool>(grid_.Columns()));
    }
    else
    {
        v = grid_.GetRow(grid_.Rows() - 2);
        if (std::find(v.begin(), v.end(), true) != v.end())
            grid_.InsertRow(grid_.Rows(), std::vector<bool>(grid_.Columns()));
    }

    v = grid_.GetColumn(grid_.Columns() - 1);
    if (std::find(v.begin(), v.end(), true) != v.end())
    {
        grid_.InsertColumn(grid_.Columns(), std::vector<bool>(grid_.Rows()));
        grid_.InsertColumn(grid_.Columns(), std::vector<bool>(grid_.Rows()));
    }
    else
    {
        v = grid_.GetColumn(grid_.Columns() - 2);
        if (std::find(v.begin(), v.end(), true) != v.end())
            grid_.InsertColumn(grid_.Columns(), std::vector<bool>(grid_.Rows()));
    }
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
