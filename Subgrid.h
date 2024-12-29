# pragma once
#include <vector>

class Subgrid{
    private:
        std::vector<std::vector<int>> cells;
        const int SUBSIZE = 3;

    public:
        Subgrid()  {cells = std::vector<std::vector<int>>(SUBSIZE, std::vector<int>(SUBSIZE, 0));};

        ~Subgrid() {};

        int getCell(int row, int col) const;

        void setCell(int row, int col, int value);
        
        bool contains(int value) const;

};