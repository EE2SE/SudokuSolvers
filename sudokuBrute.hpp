#ifndef SUDOKUBRUTE_HPP
#define SUDOKUBRUTE_HPP

#include "sudoku.hpp"

class SudokuBrute: public Sudoku
{
    public:
        using Sudoku::Sudoku;
        void solve();
};

#endif