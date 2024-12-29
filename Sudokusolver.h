# pragma once
#include "grid.h"

class SudokuSolver {
    private:
        Grid* grid;
        const int SIZE = 9;

        bool solve();

    public:
        SudokuSolver(const std::vector<std::vector<int>>& initialBoard) {
            grid = new Grid(initialBoard);
        }

        ~SudokuSolver() {
            delete grid;
        }
    
        void solveSudoku();

        Grid* solution();

        bool checkSolved() const;
        
        Grid* getGrid();

};