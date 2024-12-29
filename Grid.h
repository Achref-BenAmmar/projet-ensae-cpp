# pragma once
#include "subgrid.h"

class Grid {
    private:
        const int SIZE = 9;
        std::vector<std::vector<int>> board;
        std::vector<std::vector<Subgrid>> subgrids;
        std::vector<std::vector<bool>> initialCells;
        std::vector<std::pair<int, int>> emptyCells;
        std::vector<std::vector<bool>> errorCells;

    public:
        Grid(const std::vector<std::vector<int>>& initialBoard);

        int getCell(int row, int col) const;

        void setCell(int row, int col, int value);

        bool isSafe(int row, int col, int value) const;

        void printBoard() const;

        void markError(int row, int col, bool isError);

        bool isErrorCell(int row, int col) const;

        void printErrors() const;

        bool isSolved() const; 

        std::vector<std::pair<int, int>>& getEmptyCells();

        std::vector<std::vector<int>> getBoard() const;
};