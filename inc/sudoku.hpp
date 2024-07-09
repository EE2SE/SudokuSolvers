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
        void printSolution();
        virtual void solve();
        
        
    protected:
        string sudoku_filename;
        bool solved;
        int values[NUM_ROWS][NUM_COLS];
        int fixed_values[NUM_ROWS][NUM_COLS];
        int solution[NUM_ROWS][NUM_COLS];
        int filledSpaces;
        void readInValues();
        bool checkSolution();
        bool checkValuePossible(int valToCheck, int row, int col, int (&grid)[NUM_ROWS][NUM_COLS]);

        
};

#endif