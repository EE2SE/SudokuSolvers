#ifndef SUDOKUBRUTE_HPP
#define SUDOKUBRUTE_HPP

#include "../inc/sudoku.hpp"

class SudokuBrute: public Sudoku
{
    public:
        using Sudoku::Sudoku;
        void solve();
};

#endif