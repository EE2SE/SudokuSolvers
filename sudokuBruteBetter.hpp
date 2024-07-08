#ifndef SUDOKUBRUTEBETTER_HPP
#define SUDOKUBRUTEBETTER_HPP

#include "sudoku.hpp"

class SudokuBruteBetter: public Sudoku
{
    public:
        using Sudoku::Sudoku;
        void solve();
};

#endif