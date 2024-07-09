#ifndef SUDOKUBACKTRACKV1_HPP
#define SUDOKUBACKTRACKV1_HPP

#include "../inc/sudoku.hpp"

class SudokuBacktrackV1: public Sudoku
{
    public:
        using Sudoku::Sudoku;
        void solve();
};

#endif