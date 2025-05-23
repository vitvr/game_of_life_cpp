#include "t_display.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "matrix.h"
#include "state.h"

TDisplay::TDisplay(int x, int y) : x_ {x}, y_ {y}, x_offset_ {int((x - 1) / 2)}, y_offset_ {int((y - 1) / 2)}, screen_ {Matrix<bool>(y, x)} {}

Matrix<bool> TDisplay::Screen() { return screen_; }

void TDisplay::UpdateGame(const State& s)
{
    Matrix<bool> m = s.GetMatrix();

    // leftmost column from center (clip if out of screen bounds)
    int left_limit = std::max(-x_offset_, -s.XOffset());
    // rightmost
    int right_limit = std::min(x_ - x_offset_ - 1, s.Columns() - s.XOffset() - 1);

    int row_length = right_limit - left_limit + 1;

    int up_limit = std::max(-y_offset_, -s.YOffset());
    int down_limit = std::min(y_ - y_offset_ - 1, s.Rows() - s.YOffset() - 1);

    int column_length = down_limit - up_limit + 1;


    for (int i = 0; i != column_length; ++i)
    {
        std::vector<bool> row = m.GetSubRow(up_limit + s.YOffset() + i, left_limit + s.XOffset(), row_length);
        screen_.SetSubRow(up_limit + y_offset_ + i, left_limit + x_offset_, row);
    }
}

void TDisplay::UpdateGame(const State& s, char direction)
{
    switch (direction)
    {
        case 'u':
            ++y_offset_;
            break;
        case 'd':
            --y_offset_;
            break;
        case 'l':
            ++x_offset_;
            break;
        case 'r':
            --x_offset_;
            break;
    
    }

    UpdateGame(s);
}

void TDisplay::Print()
{
    std::cout << "\x1b[2J\x1b[H";

    int i = 0;
    for (auto p = screen_.begin(); p != screen_.end(); p = std::next(p))
    {
        if (i == screen_.Columns())
        {
            std::cout << '\n';
            i = 0;
        }

        // '#' alive, '.' dead
        std::cout << (*p ? '#' : '.');

        ++i;
    }

    std::cout << '\n';
}
