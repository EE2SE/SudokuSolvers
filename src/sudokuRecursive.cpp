#include "../inc/sudokuRecursive.hpp"
#include "../inc/sudoku.hpp"
#include <iostream>

void SudokuRecursive::solve()
{
    foundSolution = false;
    solveInternal();
}

void SudokuRecursive::solveInternal()
{
    if(!foundSolution)
    {
        for(int row = 0; row < NUM_ROWS; row++)
        {
            for(int col = 0; col < NUM_COLS; col++)
            {
                if(solution[row][col] == 0)
                {
                    for(int val = 1; val < 10; val++)
                    {
                        if(checkValuePossible(val,row,col,solution))
                        {
                            solution[row][col] = val;
                            solveInternal();
                            solution[row][col] = 0;
                        }
                    }
                    return;
                }

            }
        }
        foundSolution = true;
    }
}