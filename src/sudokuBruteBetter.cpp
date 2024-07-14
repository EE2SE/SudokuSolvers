#include "../inc/sudokuBruteBetter.hpp"
#include "../inc/sudoku.hpp"
#include <iostream>
#include <chrono>

void SudokuBruteBetter::solve()
{
    /*
        Pure brute rorce algo updates all 81 cells every time it need to change just 1 number.
        This version of the brute force will only update the required values, which should
        result in significat speed-up
    */
    auto start = std::chrono::high_resolution_clock::now();

    // initialise a 3D vector storing all non-taken values
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
                        // populate the solution with the first guess
                        if (cell_options.size() == 1)
                        {
                            solution[i][k] = checkval;
                        }
                    }
                }

                vector<int> rowColPair;
                rowColPair.push_back(i);
                rowColPair.push_back(k);
                updatableCells.push_back(rowColPair);
            }
            // cout << cell_options.size() << " ";
            // push back a counter
            cell_options.push_back(0);
            row.push_back(cell_options);
        }
        // cout << endl;
        possibleValues.push_back(row);
    }

    int updatingCellIdx = 0;
    int counter = 0;
    while (!checkSolution())
    {

        // Check elapsed time
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

        if (elapsed_ms > timeout_ms)
        {
            std::cout << "BruteForceBetter stopped due to timeout" << std::endl;
            return;
        }

        int updating_row = updatableCells[updatingCellIdx].at(0);
        int updating_col = updatableCells[updatingCellIdx].at(1);
        int last_idx = possibleValues[updating_row][updating_col].back();

        // check if there are more options in this cell
        if (last_idx < possibleValues[updating_row][updating_col].size() - 2)
        {
            // if there, set it to try the next option and don't change the updating cell
            possibleValues[updating_row][updating_col].pop_back();
            possibleValues[updating_row][updating_col].push_back(++last_idx);
            solution[updating_row][updating_col] = possibleValues[updating_row][updating_col].at(last_idx);
            // cout << "Updating " << updating_row << " " << updating_col << endl;
        }
        else // otherwise we need to go to the next incrementable cell and increment that one while resetting all the previous ones
        {
            while (last_idx >= possibleValues[updating_row][updating_col].size() - 2)
            {
                possibleValues[updating_row][updating_col].pop_back();
                possibleValues[updating_row][updating_col].push_back(0);
                solution[updating_row][updating_col] = possibleValues[updating_row][updating_col].at(0);
                // cout << "Resetting " << updating_row << " " << updating_col << endl;
                updatingCellIdx++;
                if (updatingCellIdx == updatableCells.size())
                {
                    cout << "NO SOLUTION FOUND!" << endl;
                    return;
                }

                updating_row = updatableCells[updatingCellIdx].at(0);
                updating_col = updatableCells[updatingCellIdx].at(1);
                last_idx = possibleValues[updating_row][updating_col].back();
            }
            // cout << "Updating " << updating_row << " " << updating_col << endl;
            possibleValues[updating_row][updating_col].pop_back();
            possibleValues[updating_row][updating_col].push_back(++last_idx);
            solution[updating_row][updating_col] = possibleValues[updating_row][updating_col].at(last_idx);
            // cout << "Updating " << updating_row << " " << updating_col << endl;
            updatingCellIdx = 0;
        }
        counter++;
    }
}