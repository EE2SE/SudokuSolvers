#include "sudoku.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atoi */
#include <map>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

Sudoku::Sudoku()
{
    cout<<"Please provide a text file"<<endl;
}

Sudoku::Sudoku(string filename)
{
    sudoku_filename = filename;
    readInValues();
}

void Sudoku::readInValues()
{
    ifstream myfile;
    char val;
    short row(0);
    short column(0);

    myfile.open(sudoku_filename);
    if ( myfile.is_open() ) { // always check whether the file is open
        while(!myfile.eof())
        {
            myfile.get(val);
            if(!myfile.eof())
            {
                if(val == 10)
                {
                    cout << " |" << endl;
                    cout << "- - - - - - - - - - - - - - - - - - - -" << endl;
                }
                else
                {
                    
                    values[row][column] = int(val - '0');
                    solution[row][column] = int(val - '0');
                    fixed_values[row][column] = (int(val - '0') == 0) ? 0 : 1;
                    filledSpaces += fixed_values[row][column];
                    cout <<  " | "<< values[row][column];
                    column++;
                    if(column == NUM_COLS)
                    {
                        row = (row+1)%NUM_ROWS;
                        column = 0;
                    } 
                }
            }
            else
            {
                cout << " |" << endl;
            }
           
            

        }
    }

    myfile.close();
}

void Sudoku::printSolution()
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for(int k = 0; k < NUM_COLS; k++)
        {
            cout <<  " | " << solution[i][k];
        }
        cout << " |" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - -" << endl;
    }
}

bool Sudoku::solveBetterBruteForce()
{
        /*
        Pure brute rorce algo updates all 81 cells every time it need to change just 1 number.
        This version of the brute force will only update the required values, which should
        result in significat speed-up
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
                for(int checkval = 0; checkval < 8; checkval++)
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
                totalCombinations *= cell_options.size();
            }
            cout << cell_options.size() << " ";
            // push back a counter
            cell_options.push_back(0);
            row.push_back(cell_options);
        }
        cout << endl;
        possibleValues.push_back(row);
    }

    return true;


}

bool Sudoku::solveBruteForce()
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
            cout << cell_options.size() << " ";
            // push back a counter
            cell_options.push_back(0);
            row.push_back(cell_options);
        }
        cout << endl;
        possibleValues.push_back(row);
    }

    // now iterate over all possible number combinations 
    int updatingCellIdx = 0;
    int counter = 1;
    cout << totalCombinations << endl;
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

        if(counter%1000000 == 0)
        {
            cout << "Attempt: " << counter << "/" << totalCombinations << ". Completed: " << 100.0f*(float)counter/(float)totalCombinations <<endl;
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
                    return false;
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

    printSolution();
    return true;

}

bool Sudoku::checkValuePossible(int valToCheck, int row, int col)
{
    for(int i = 0; i < NUM_COLS; i++)
    {
        if(values[row][i] == valToCheck)
        {
            // cout << "In column-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
            return false;
        }
    }

    for(int i = 0; i < NUM_ROWS; i++)
    {
        if(values[i][col] == valToCheck)
        {
            // cout << "In row-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
            return false;
        }
    }

    // since we checked row and column at this stage
    // we only need to check 4 values in the box
    // row = 4, we just need to check row 3 and row 5
    // so somehow we need row -1 and row +1
    // 4%3 = 1
    // row = 3, check row+1 row+2 => 3%3 = 0
    // row = 4, check row-1 row+1 => 4%3 = 1
    // row = 5, check row-2 row -1 => 5%3 = 2
    
    switch(row%3)
    {
        case 0:
            switch(col%3)
            {
                case 0:
                    if((values[row+1][col+1] == valToCheck) || (values[row+2][col+1] == valToCheck) || (values[row+1][col+2] == valToCheck) || (values[row+2][col+2] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;

                case 1:
                    if((values[row+1][col+1] == valToCheck) || (values[row+2][col+1] == valToCheck) || (values[row+1][col-1] == valToCheck) || (values[row+2][col-1] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;

                case 2:
                    if((values[row+1][col-1] == valToCheck) || (values[row+2][col-1] == valToCheck) || (values[row+1][col-2] == valToCheck) || (values[row+2][col-2] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;
            }
        break;

        case 1:
            switch(col%3)
            {
                case 0:
                    if((values[row-1][col+1] == valToCheck) || (values[row+1][col+1] == valToCheck) || (values[row-1][col+2] == valToCheck) || (values[row+1][col+2] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;

                case 1:
                    if((values[row-1][col+1] == valToCheck) || (values[row+1][col+1] == valToCheck) || (values[row-1][col-1] == valToCheck) || (values[row+1][col-1] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;

                case 2:
                    if((values[row-1][col-1] == valToCheck) || (values[row+1][col-1] == valToCheck) || (values[row-1][col-2] == valToCheck) || (values[row+1][col-2] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;
            }
        break;

        case 2:
            switch(col%3)
            {
                case 0:
                    if((values[row-1][col+1] == valToCheck) || (values[row-2][col+1] == valToCheck) || (values[row-1][col+2] == valToCheck) || (values[row-2][col+2] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;

                case 1:
                    if((values[row-1][col+1] == valToCheck) || (values[row-2][col+1] == valToCheck) || (values[row-1][col-1] == valToCheck) || (values[row-2][col-1] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;

                case 2:
                    if((values[row-1][col-1] == valToCheck) || (values[row-2][col-1] == valToCheck) || (values[row-1][col-2] == valToCheck) || (values[row-2][col-2] == valToCheck))
                    {
                        // cout << "In box-> " <<"Value: " << valToCheck << "In :" << row << " " << col << endl;
                        return false;
                    }
                break;
            }
        break;
    }
    

    return true;

}

bool Sudoku::checkSolution()
{
    // each row must have unique numbers
    bool validSolution = true;
    for (int i = 0; i < NUM_ROWS; i++)
    {
        map<int, bool> rowValues;
        for(int k = 0; k< NUM_COLS; k++)
        {
            if (rowValues.find(solution[i][k]) == rowValues.end()) {
                // not found
                rowValues.insert (pair<int,bool>(solution[i][k],true) );
            } else {
                // found
                validSolution = false;
                break;
            }
        }
        if(!validSolution)
        {
            break;
        }
    }

    // each column must have unique numbers
    for (int i = 0; i < NUM_COLS; i++)
    {
        map<int, bool> colValues;
        for(int k = 0; k< NUM_ROWS; k++)
        {
            if (colValues.find(solution[k][i]) == colValues.end()) {
                // not found
                colValues.insert (pair<int,bool>(solution[k][i],true) );
            } else {
                // found
                validSolution = false;
                break;
            }
        }
        if(!validSolution)
        {
            break;
        }
    }

    for (int i = 0; i < MINOR_ROWS; i++)
    {
        for (int k = 0; k < MINOR_COLS; k++)
        {
            map<int, bool> boxValues;
            for(int mi = 0; mi < MINOR_ROWS; mi++)
            {
                for(int mk = 0; mk < MINOR_COLS; mk++)
                {
                    if (boxValues.find(solution[3*i + mi][3*k + mk]) == boxValues.end()) {
                        // not found
                        boxValues.insert (pair<int,bool>(solution[3*i + mi][3*k + mk],true) );
                    } else {
                        // found
                        validSolution = false;
                        break;
                    }
                }
            }
            if(!validSolution)
            {
                break;
            }
        }

        if(!validSolution)
        {
            break;
        }
    }

    return validSolution;

}