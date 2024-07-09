#ifndef SUDOKUBACKTRACKV2_HPP
#define SUDOKUBACKTRACKV2_HPP

#include "../inc/sudoku.hpp"

class SudokuBacktrackV2: public Sudoku
{
    public:
        using Sudoku::Sudoku;
        void solve();
};

#endif