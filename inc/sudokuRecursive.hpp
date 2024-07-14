#ifndef SUDOKURECUSRIVE_HPP
#define SUDOKURECUSRIVE_HPP

#include "../inc/sudoku.hpp"

class SudokuRecursive: public Sudoku
{
    public:
        using Sudoku::Sudoku;
        void solve();
    private:
        void solveInternal();
        bool foundSolution;
        
};

#endif