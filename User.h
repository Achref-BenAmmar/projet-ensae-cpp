# pragma once
#include "Sudokusolver.h"
#include <vector>

class User {
    private:
        Grid* grid;
        std::vector<std::vector<int>> solutionBoard;
        std::vector<std::vector<bool>> initialCells;
        std::vector<std::vector<int>> initialBoard;

    public:
        User(Grid* g, const std::vector<std::vector<int>>& initialBoard);

        void addNumber(int row, int col, int value);

        void getHint(int row, int col);

        void userInput();


};