#ifndef LIFE_STATE_H_
#define LIFE_STATE_H_

#include <string>
#include <vector>

#include "matrix.h"

class State
{
    public:
        State(Matrix<bool> grid);

        Matrix<bool> GetMatrix();
        int YOffset();
        int XOffset();

        // State Step();
        
    private:
        Matrix<bool> grid_;

        // coordinates of top left corner relative to center
        // to keep track of cells' fixed position as matrix is resized
        int y_offset_;
        int x_offset_;
        
        // int CountNeighbors();
        // void AddMargin();
};

#endif
