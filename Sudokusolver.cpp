#include "Sudokusolver.h"
#include <iostream>

using namespace std;

bool SudokuSolver::solve() {
    //Solve the current sudoku board using the backtracking algorithm
    //Return true after solving the board or false if the puzzle is unsolvable

        int row, col;
        
        static vector<pair<int, int>> emptyCells = grid->getEmptyCells();

        if (emptyCells.empty())
            return true; // No empty space left

        row = emptyCells.back().first;
        col = emptyCells.back().second;
        emptyCells.pop_back();

        for (int num = 1; num <= SIZE; ++num) {
            if (grid->isSafe(row, col, num)) {
                grid->setCell(row, col, num);

                if (solve())
                    return true;

                grid->setCell(row, col, 0); // Backtrack
            }
        }

        emptyCells.push_back({row, col});
        return false; // Trigger backtracking
};

void SudokuSolver::solveSudoku() {
    //Solve the current sudoku board 

        if (!solve()) {
            cout << "No solution exists for the given Sudoku." << endl;
        }
};

Grid* SudokuSolver::solution() {
    //Return the current's board solution

    //Check if the board is already solved
    if(grid->isSolved()) {
        return grid;
    }
    else if (solve()) { 
        return grid;
    }
    else {
        cout << "No solution exists for the given Sudoku." << endl;
        return 0;
    }

    
};

bool SudokuSolver::checkSolved() const {
    //Return whether the current board is already solved or not

        return grid->isSolved();
    }

Grid* SudokuSolver::getGrid() {
    //Return the current sudoku board

        return grid;
    }


