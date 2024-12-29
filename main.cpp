#include "Subgrid.h"
#include "Grid.h"
#include "Sudokusolver.h"
#include "User.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


#include <SFML/Graphics.hpp>

using namespace std;


//Declaration of functions used to randomly select a sudoku puzzle from text file with a list of multiple puzzles
vector<vector<int>> puzzlefromtxt(const string& line);
vector<vector<vector<int>>> readfilepuzzle(const string& filename);
vector<vector<int>> randomgrid(const vector<vector<vector<int>>>& puzzle_list);


//Declaration of graphic functions used to display buttons
void drawGrid(sf::RenderWindow& window, const vector<vector<int>>& board, const int GRIDSIZE, Grid* grid, int selectedrow, int selectedcol);
void drawButtons(sf::RenderWindow& window, const int BUTTONSIZE);

//Declaration of the size of a single cell of the sudoku board
int CELLSIZE = 75u;

//Selection of the background's color
sf::Color backgroundclr(245,245,245);

int main(){

    //Randomly select a sudoku puzzle from text file
    vector<vector<int>> initialBoard = randomgrid(readfilepuzzle("data\\Grids_puzzles.txt"));


    vector<vector<bool>> errorcells(9,vector<bool>(9, false));

    SudokuSolver solver(initialBoard);
    User user(solver.getGrid(), initialBoard);


    sf::Vector2i selectedCell(-1, -1);
    int selectedNum = 0;


    auto window = sf::RenderWindow(sf::VideoMode({1024u, 768u}), "Sudoku Solver Project");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }


        //Get user mouse inputs and executes desired task when the mouse is clicked based on its position relative to the window
            if (event->is<sf::Event::MouseButtonPressed>()) {
                int x = (sf::Mouse::getPosition(window).x-1) / CELLSIZE;
                int y = (sf::Mouse::getPosition(window).y-50) / CELLSIZE;
                if (x >= 0 && x < 9 && y >= 0 && y < 9) {
                    selectedCell = sf::Vector2i(x, y);
                }
                else if (x == 12){
                    selectedNum = (sf::Mouse::getPosition(window).y - 20) / (CELLSIZE*1.1);
                    selectedNum %= 9;
                    if (selectedCell != sf::Vector2i(-1,-1)){
                        user.addNumber(selectedCell.y,selectedCell.x,selectedNum + 1);
                    }
                }
                else if (x >=9 && x < 12 && (y == 7 || y == 8)){
                    if (selectedCell != sf::Vector2i(-1,-1)){
                        user.getHint(selectedCell.y,selectedCell.x);
                    }
                }
            }
        }

        //Clear the window and display all elements on screen

        window.clear(backgroundclr);
        drawGrid(window, solver.getGrid()->getBoard(),CELLSIZE,solver.getGrid(),selectedCell.y,selectedCell.x);
        drawButtons(window, 75u);
        window.display();
    }

    //Continue the puzzle using the console after closing the window

    solver.getGrid()->printBoard();
    user.userInput();



    return 0;
}





vector<vector<int>> puzzlefromtxt(const string& line) {
    //Convert a line of text of a single puzzle with a specific format to a 2D vector

    vector<vector<int>> puzzle(9, vector<int>(9,0));
    for(int i = 0; i < line.size(); i++){
        if (line[i] == '.') {
            puzzle[i / 9][i % 9] = 0; // Convert '.' to 0
        } else {
            puzzle[i / 9][i % 9] = line[i] - '0'; // Convert char digit to int
        }
    }
    return puzzle;
}

vector<vector<vector<int>>> readfilepuzzle(const string& filename){
    //Return a list of 2D vectors of the available puzzle boards read from a text file

    ifstream file(filename);
    vector<vector<vector<int>>> puzzle_list;
    string line;

    while (getline(file, line, ',')) {
        if (line[0] == '\n') {
            line.erase(0,1);
        }
        if (!line.empty()) {
            puzzle_list.push_back(puzzlefromtxt(line));
        }
    }

    file.close();

    return(puzzle_list);
}

vector<vector<int>> randomgrid(const vector<vector<vector<int>>>& puzzle_list) {
    //Select a random board from a list of puzzles

    //Set a new seed based on the machine's time
    srand(time(0));
    int puzzle_nb = rand() % (puzzle_list.size()+1);
    return puzzle_list[puzzle_nb];
}


void drawGrid(sf::RenderWindow& window, const vector<vector<int>>& board, const int CELLSIZE, Grid* grid, int selectedrow, int selectedcol) {

    //Display the current sudoku board on screen

    sf::RectangleShape cell(sf::Vector2f(CELLSIZE, CELLSIZE));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Black);

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            //Display empty cells

            cell.setPosition(sf::Vector2f(10+ j * CELLSIZE, 50 + i * CELLSIZE));
            if(selectedrow == i && selectedcol == j){
                cell.setFillColor(sf::Color(173,216,230));
            }
            window.draw(cell);
            cell.setFillColor(sf::Color::White);

        if (board[i][j] != 0) {
            //Display the number within the non-empty cells

                const sf::Font font("data\\arial.ttf");
                sf::Text text(font, to_string(board[i][j]));
                text.setCharacterSize(24*CELLSIZE/50u);

                //Change the color of wrong cells
                if(grid->isErrorCell(i,j)){
                    text.setFillColor(sf::Color::Red);
                }
                else {
                    text.setFillColor(sf::Color::Black);
                }
                text.setPosition(sf::Vector2f(10 + j * CELLSIZE + CELLSIZE / 3, 50 + i * CELLSIZE + CELLSIZE / 4));
                window.draw(text);


            }
        }
    }


    //Display the board separators
    sf::RectangleShape boldLine;
    boldLine.setFillColor(sf::Color::Black);
    for (int i = 1; i < 3; ++i) {
        //Horizontal separators
            boldLine.setSize(sf::Vector2f(CELLSIZE * 9, 5));
            boldLine.setPosition(sf::Vector2f(10, 50 + i * 3 * CELLSIZE));
            window.draw(boldLine);
        //Vertical separators
            boldLine.setSize(sf::Vector2f(5, CELLSIZE * 9));
            boldLine.setPosition(sf::Vector2f(10 + i * 3 * CELLSIZE, 50));
            window.draw(boldLine);
    }
}

void drawButtons(sf::RenderWindow& window, const int BUTTONSIZE) {
    //Display buttons on the screen

    sf::RectangleShape button(sf::Vector2f(BUTTONSIZE, BUTTONSIZE));
    button.setOutlineThickness(1);
    button.setOutlineColor(sf::Color::Black);


    //Display number buttons
    for (int i = 1; i <= 9; ++i) {
        //Display empty buttons
        button.setFillColor(sf::Color(173,216,230));
        button.setPosition(sf::Vector2f(12 * CELLSIZE, (i - 1) * BUTTONSIZE * 1.1 + 20));
        window.draw(button);


        //Display numbers
        const sf::Font font("data\\arial.ttf");
        sf::Text text(font, to_string(i));
        text.setCharacterSize(24*BUTTONSIZE/50u);
        text.setFillColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(12 * CELLSIZE + BUTTONSIZE /3,((i - 1) * BUTTONSIZE + BUTTONSIZE / 4) * 1.1 + 20));
        window.draw(text);
    }

    //Display the hint button
    button.setSize(sf::Vector2f(2.5*BUTTONSIZE, 1.75*BUTTONSIZE));
    button.setFillColor(sf::Color(173,216,230));
    button.setPosition(sf::Vector2f(9.33 * CELLSIZE, 7 * BUTTONSIZE * 1.05 + 50));
    window.draw(button);

    const sf::Font font("data\\arial.ttf");
    sf::Text text(font, "Hint");
    text.setCharacterSize(2 * 24*BUTTONSIZE/50u);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(9.33 * CELLSIZE + BUTTONSIZE *1/3, 7 * BUTTONSIZE * 1.05 + BUTTONSIZE/4 + 50));
    window.draw(text);

}