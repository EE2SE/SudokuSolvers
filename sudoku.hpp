#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <string>

using namespace std;

class Sudoku
{
    public:
        Sudoku(string filename);
        Sudoku();
        bool solve();
        void readInValues();
        void printSolution();

    private:
        bool solved;
        int values[9][9];
        bool fixed_values[9][9];
};

#endif