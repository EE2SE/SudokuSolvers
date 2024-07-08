#include "../inc/sudokuBrute.hpp"
#include "../inc/sudoku.hpp"
#include <iostream>

void SudokuBrute::solve()
{
       /*
        Brute Force tries every single number combination blindly.
        E.g. it will start by filling all values with 1111, then 1112 etc.
        This will probably not even work because to try all 9 numbers in
        at worst 81 different squares will require something like 1e77 total tries.

        So we can do a little better but still brute force. We can determine every
        single possible value for each cell and then only try those. So if in row (a)
        we have a fixed 5, we won't brute force insert 5 into any cell in that row
    */

    int totalCombinations = 1; 

    // initialise a 3D vector storing all non-taken values
     vector< vector< vector<int> > > possibleValues;
     vector<vector<int> > updatableCells;
    for (int i = 0; i < NUM_ROWS; i++)
    {
        vector< vector<int> > row;
        for(int k = 0; k< NUM_COLS; k++)
        {
            vector<int> cell_options;
            if(fixed_values[i][k] == 0)
            {
                for(int checkval = 1; checkval < 10; checkval++)
                {
                    if(checkValuePossible(checkval, i, k))
                    {
                        cell_options.push_back(checkval);
                    }
                }

                vector<int> rowColPair;
                rowColPair.push_back(i);
                rowColPair.push_back(k);
                updatableCells.push_back(rowColPair);
                totalCombinations *= cell_options.size(); // this is overflowing as the real number is of the order of 1e19
            }
            // cout << cell_options.size() << " ";
            // push back a counter
            cell_options.push_back(0);
            row.push_back(cell_options);
        }
        // cout << endl;
        possibleValues.push_back(row);
    }

    // now iterate over all possible number combinations 
    int updatingCellIdx = 0;
    int counter = 1;
    // cout << totalCombinations << endl;
    while(!checkSolution())
    {
        // insert numbers
        for (int i = 0; i < NUM_ROWS; i++)
        {
            for (int k = 0; k < NUM_COLS; k++)
            {
                if(fixed_values[i][k] == 0)
                {
                    // idx - position in the vector of availbale options for the given cell to try out
                    int idx = possibleValues[i][k].back();
                    // insert the possible value from vector[idx] for the given cell
                    solution[i][k] = possibleValues[i][k].at(idx);
                }
            }
        }

        counter++;
        //once we updated 81 cells update vectors and indicies.
        // fetch currently used cell
        // actually at this stage updatingCellIdx is always 0.
        int updating_row = updatableCells[updatingCellIdx].at(0);
        int updating_col = updatableCells[updatingCellIdx].at(1);
        int last_idx = possibleValues[updating_row][updating_col].back();
        // check if there are more options in this cell
        if(last_idx < possibleValues[updating_row][updating_col].size()-2)
        {
            // if there, set it to try the next option and don't change the updating cell
            possibleValues[updating_row][updating_col].pop_back();
            possibleValues[updating_row][updating_col].push_back(++last_idx);
        }
        else // otherwise we need to go to the next incrementable cell and increment that one while resetting all the previous ones
        {
            while(last_idx >= possibleValues[updating_row][updating_col].size()-2)
            {
                possibleValues[updating_row][updating_col].pop_back();
                possibleValues[updating_row][updating_col].push_back(0);
                updatingCellIdx++;
                if(updatingCellIdx == updatableCells.size())
                {
                    cout << "NO SOLUTION FOUND!" << endl;
                    return;

                }

                updating_row = updatableCells[updatingCellIdx].at(0);
                updating_col = updatableCells[updatingCellIdx].at(1);
                last_idx = possibleValues[updating_row][updating_col].back();
            }

            possibleValues[updating_row][updating_col].pop_back();
            possibleValues[updating_row][updating_col].push_back(++last_idx);
            updatingCellIdx = 0;
        }
        
    }
 
}