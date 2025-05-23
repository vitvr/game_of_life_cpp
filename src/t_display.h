#ifndef LIFE_T_DISPLAY_H_
#define LIFE_T_DISPLAY_H_

#include "matrix.h"
#include "state.h"

class TDisplay
{
    public:
        TDisplay(int x, int y);
        void UpdateGame(const State& s);
        void UpdateGame(const State& s, char direction);
        void Print();
        Matrix<bool> Screen();

    private:
        Matrix<bool> screen_;
        // coordinates of center relative to (0, 0) (left corner)
        // to keep track of cells' fixed position as user moves the screen
        int x_offset_;
        int y_offset_;
        int x_;
        int y_;
};

# endif
