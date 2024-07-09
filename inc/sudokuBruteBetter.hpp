#ifndef SUDOKUBRUTEBETTER_HPP
#define SUDOKUBRUTEBETTER_HPP

#include "../inc/sudoku.hpp"

class SudokuBruteBetter: public Sudoku
{
    public:
        using Sudoku::Sudoku;
        void solve();

};

#endif