#ifndef LIFE_STATE_H_
#define LIFE_STATE_H_

#include "matrix.h"

class State
{
    public:
        State();
        State(Matrix<bool> grid);

        Matrix<bool> GetMatrix() const;
        int YOffset() const;
        int XOffset() const;

        int Rows() const;
        int Columns() const;
        
        void Step();
        
    private:
        Matrix<bool> grid_;

        // coordinates of center relative to (0, 0) (left corner)
        // to keep track of cells' fixed position as matrix is resized
        int y_offset_;
        int x_offset_;
        
        // int CountNeighbors();
        void AddMargin();
};

#endif
