#include "User.h"
#include <iostream>
using namespace std;


User::User(Grid* g, const vector<vector<int>>& initialBoard) : grid(g){
    this->initialBoard = initialBoard;
    initialCells.resize(9, vector<bool>(9, false));
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (initialBoard[i][j] != 0)
                initialCells[i][j] = true;

    //Create a SudokuSolver instance, solves the board and saves it as the matrix solutionBoard

    SudokuSolver solver(initialBoard);
    solver.solveSudoku();
    solutionBoard = solver.getGrid()->getBoard();
};

void User::addNumber(int row, int col, int value) {
    //Set the value of a cell initially empty

        if (initialCells[row][col]) {
            std::cout << "Cell is part of the initial puzzle and cannot be changed." << endl;
            return;
        }
        
        grid->setCell(row, col, value);
        std::cout << "Number " << value << " added at (" << row + 1 << ", " << col + 1 << ")." << endl;


    // Record wrong cells    
    if(solutionBoard[row][col] != value){
        grid->markError(row,col,true);
        }
    else {
        grid->markError(row,col,false);
    }
};

void User::getHint(int row, int col){
    //Return the correct value of a cell

    if (initialCells[row][col]) {
            std::cout << "Cell is part of the initial puzzle and cannot be changed." << endl;
            return;
        }
    grid->setCell(row , col, solutionBoard[row][col]);
    grid->markError(row,col,false);
    std::cout << "Hint provided successfully at (" << row + 1 << "," << col + 1 << ")" << endl;
}

void User::userInput() {
    //Allow user inputs through the console in order to fill a cell or ask for a hint

    int row, col, value;
    char choice;
    do {
        choice = 'y';
        cout << "Enter row (1-9), column (1-9), and value (1-9) to place or enter (0) for a hint: \n";
        cin >> row;
        if (row == 0){
            cout << "Enter row (1-9), column (1-9) of the cell to reveal: \n";
            cin >> row >> col;
            if (row < 1 || row > 9 || col < 1 || col > 9 ) {
                cout << "Invalid input. Please enter numbers between 1 and 9 or 0 for a hint." << endl;
            continue;
            }
            getHint(row - 1, col - 1);
            grid->printBoard();
            grid->printErrors();
            cout << "Do you want to add another number? (y/n) : ";
            cin >> choice;
            continue;
        }
        cin >> col >> value;

        if (row < 1 || row > 9 || col < 1 || col > 9 || value < 1 || value > 9) {
            cout << "Invalid input. Please enter numbers between 1 and 9 or 0 for a hint." << endl;
            continue;
        }

        addNumber(row - 1, col - 1, value);
        grid->printBoard();
        grid->printErrors();

        cout << "Do you want to add another number? (y/n) : ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Final board: " << endl;
    grid->printBoard();
};