#include "Grid.h"
#include <iostream>

using namespace std;

Grid::Grid(const vector<vector<int>>& initialBoard) : board(SIZE, vector<int>(SIZE, 0)), subgrids(3, vector<Subgrid>(3)), errorCells(SIZE, vector<bool>(SIZE, false)), initialCells(SIZE, vector<bool>(SIZE, false)) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int value = initialBoard[i][j];
                board[i][j] = value;
                if (value != 0) {
                    subgrids[i / 3][j / 3].setCell(i % 3, j % 3, value);
                    initialCells[i][j] = true;
                } else {
                    emptyCells.push_back({i, j}); // Record empty cells
                }
            }
        }
};

int Grid::getCell(int row, int col) const {
    // Return the value of a cell

        return board[row][col];
    };

void Grid::setCell(int row, int col, int value) {
    // Change the value of a cell

        board[row][col] = value;
        subgrids[row / 3][col / 3].setCell(row % 3, col % 3, value);
    };

bool Grid::isSafe(int row, int col, int value) const {
    // Check if the entered value is legal relative to sudoku rules

        for (int x = 0; x < SIZE; ++x) {
            if (board[row][x] == value || board[x][col] == value)
                return false;
        }
        return !subgrids[row / 3][col / 3].contains(value);
    };


void Grid::printBoard() const {
    //Print the current sudoku board in the console
    //Used primarily for debugging

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0 && j != 0) cout << " | "; // Add vertical separators
                if (board[i][j] == 0)
                    cout << "."; // Display empty cells as dots
                else
                    cout << board[i][j];
                cout << " ";
            }
            cout << endl;
            if ((i + 1) % 3 == 0 && i != SIZE - 1) {
                // Add horizontal separators
                cout << string(21, '-') << endl;
            }
        }
    };

void Grid::markError(int row, int col, bool isError) {
    //Sets the state of a cell recording whether its wrong or correct

        errorCells[row][col] = isError;
    };

bool Grid::isErrorCell(int row, int col) const {
    //Return the state of a cell

        return errorCells[row][col];
    };

void Grid::printErrors() const {
    //Print in the console the list of coordonates of wrong cells in the current sudoku board

        cout << "Cells with errors:" << endl;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (errorCells[i][j])
                    cout << "Error at cell (" << i + 1 << ", " << j + 1 << ")" << endl;
            }
        }
    };

bool Grid::isSolved() const {
    //Check if the current sudoku board is solved

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == 0 || errorCells[i][j])
                    return false;
            }
        }
        return true;
    };

vector<pair<int, int>>& Grid::getEmptyCells() {
    //Return current board's empty cells

        return emptyCells;
    };

vector<vector<int>> Grid::getBoard() const {
    //Return the current sudoku board

            return board;
        }