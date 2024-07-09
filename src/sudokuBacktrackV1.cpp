#include "../inc/sudokuBacktrackV1.hpp"
#include "../inc/sudoku.hpp"
#include <iostream>

void SudokuBacktrackV1::solve()
{
    /*
        Rather than filling all spots and only then checking if thew solution is valid,
        BacktrackingV1 fills in 1 cell at a time and checks whether the inserted number
        violates the sudoku. If it does, next one is chosen and it is rechecked.
        If no values are valid in the cell, we know the mistake lives before.

        This is known as depth-first search algortihm. It checks the entire branch first.

    */

    vector<vector<vector<int>>> possibleValues;
    vector<vector<int>> updatableCells;
    for (int i = 0; i < NUM_ROWS; i++)
    {
        vector<vector<int>> row;
        for (int k = 0; k < NUM_COLS; k++)
        {
            vector<int> cell_options;
            if (fixed_values[i][k] == 0)
            {
                for (int checkval = 1; checkval < 10; checkval++)
                {
                    if (checkValuePossible(checkval, i, k, values))
                    {
                        cell_options.push_back(checkval);
                    }
                }

                vector<int> rowColPair;
                rowColPair.push_back(i);
                rowColPair.push_back(k);
                updatableCells.push_back(rowColPair);
              
            }

            // push back a counter
            cell_options.push_back(0);
            row.push_back(cell_options);
        }
        // cout << endl;
        possibleValues.push_back(row);
    }

    // try cell 1, val 1 and check if it works

    
    bool solved = false;
    int cell_ctr = 0;
    while(!solved)
    {
        int row = updatableCells[cell_ctr].at(0);
        int col = updatableCells[cell_ctr].at(1);
        int idx = possibleValues[row][col].back();
        int val_to_test = possibleValues[row][col].at(idx);

        // check if value can be assigned to current cell
        if(checkValuePossible(val_to_test, row, col, solution))
        {
            solution[row][col] = val_to_test;
            if(cell_ctr == updatableCells.size()-1)
            {
                solved = true;
            }
            else
            {
                cell_ctr++;
            }
        }
        // if the value cannt be assigned to the cell
        else
        {
            //set up next value in the vector to be checked next
            //and just clear the current cell for good measure
            solution[row][col] = 0;
            idx++;
            // if there are no more values to be tried out in this cell
            // we need to backtrack
            if(idx > possibleValues[row][col].size()-2)
            {
                idx = 0;
                // if there is more room to backtrack we exit without a solution
                if(cell_ctr == 0)
                {
                    cout << "NO SOLUTION POSSIBLE" << endl;
                    break;
                }
                else
                {
                    cell_ctr--;
                }
            }
            possibleValues[row][col].pop_back();
            possibleValues[row][col].push_back(idx);
        }
    }

    if(solved)
    {
        if(!checkSolution())
        {
            cout << "SOLUTION WRONG" << endl;
        }

    }
};
