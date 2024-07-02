#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <string>

#define NUM_ROWS 9
#define NUM_COLS 9
#define MINOR_ROWS 3
#define MINOR_COLS 3

using namespace std;

class Sudoku
{
    public:
        Sudoku(string filename);
        Sudoku();
        bool solve();
        void printSolution();

    private:
        string sudoku_filename;
        bool solved;
        int values[9][9];
        bool fixed_values[9][9];

        void readInValues();
};

#endif