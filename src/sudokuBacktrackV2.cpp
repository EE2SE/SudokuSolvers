#include "../inc/sudokuBacktrackV2.hpp"
#include "../inc/sudoku.hpp"
#include <iostream>

void SudokuBacktrackV2::solve()
{
    /*
        V1 as well as all brute force algos don't really use any
        Sudoku solving cleverness. They try numbers until they
        solve it or run out of options.

        We can use some celeverness. For instance: when we build
        our vector of all possible values for each cell, if there 
        is just a single option, we might as well immiadiately 
        fill it in and use this information to clean up the list
        of options.

    */

    vector<vector<vector<int>>> possibleValues;
    vector<vector<int>> updatableCells;
    bool fewerCells = true;
    while (fewerCells)
    {
        fewerCells = false;
        vector<vector<vector<int>>> possibleValuesTemp;
        vector<vector<int>> updatableCellsTemp;

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
                        if (checkValuePossible(checkval, i, k, solution))
                        {
                            cell_options.push_back(checkval);
                        }
                    }
                    if (cell_options.size() == 1)
                    {
                        solution[i][k] = cell_options.back();
                        fixed_values[i][k] = 1;
                        fewerCells = true;
                    }
                    else
                    {
                        vector<int> rowColPair;
                        rowColPair.push_back(i);
                        rowColPair.push_back(k);
                        updatableCellsTemp.push_back(rowColPair);
                    }
                }

                // push back a counter
                cell_options.push_back(0);
                row.push_back(cell_options);
            }
            // cout << endl;
            possibleValuesTemp.push_back(row);
        }
        possibleValues = possibleValuesTemp;
        updatableCells = updatableCellsTemp;
    }

    // try cell 1, val 1 and check if it works
    
    bool solved = false;
    int cell_ctr = 0;
    if(updatableCells.size() == 0) solved = true;
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
