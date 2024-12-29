#Sudoku Solver Project

This project is a Sudoku solver application built using C++ and the SFML library. The executable is statically built, meaning SFML is included directly in the executable and does not require SFML to be installed on your system.

## Folder Structure

The project folder contains the following files:

- **Headers**:
  - `Subgrid.h`
  - `Grid.h`
  - `Sudokusolver.h`
  - `User.h`

- **Source Files**:
  - `Subgrid.cpp`
  - `Grid.cpp`
  - `Sudokusolver.cpp`
  - `User.cpp`
  - `main.cpp`

## Requirements

MSYS2: Install MSYS2 from msys2.org if you don't have it already.

Compilation Instructions

Open the MSYS2 ucrt64 terminal.

Navigate to the project directory.

Compile the code with the following command:

```
g++ main.cpp Subgrid.cpp Grid.cpp Sudokusolver.cpp User.cpp -Iinclude -Llib -lsfml-graphics -lsfml-window -lsfml-system -o Sudoku_Solver_project.exe
```

This command dynamically links the SFML libraries, so make sure the required SFML DLL files are present in the same directory as the executable or accessible via the system PATH.

## Running the Program

In the project folder, you will find an executable file named Sudoku Solver Project.exe. This executable was generated using CMake and is designed to run on Windows. Since it is statically built, you do not need to install SFML or any additional libraries.

Simply double-click the executable to launch the Sudoku solver application.

