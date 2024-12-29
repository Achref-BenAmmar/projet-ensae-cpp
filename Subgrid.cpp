#include "Subgrid.h"



int Subgrid::getCell(int row, int col) const {
    // Return the value of a cell

        return cells[row][col];
    };

void Subgrid::setCell(int row, int col, int value) {
    // Change the value of a cell

        cells[row][col] = value;
    };

bool Subgrid::contains(int value) const {
    // Check if the Subgrid contains already a cell having the entered value

        for (int i = 0; i < SUBSIZE; i++)
            for (int j = 0; j < SUBSIZE; j++)
                if (cells[i][j] == value)
                    return true;
        return false;
    };