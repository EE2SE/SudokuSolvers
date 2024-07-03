#include "../inc/sudoku.hpp"
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
            cout <<  " | " << values[i][k];
        }
        cout << " |" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - -" << endl;
    }
}

void Sudoku::solveBruteForce()
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

    // now iterate over all possible number combinations 
    int updatingCellIdx = 0;
    int counter = 1;
    while(!checkSolution())
    {
        // insert numbers
        for (int i = 0; i < NUM_ROWS; i++)
        {
            for (int k = 0; k < NUM_COLS; k++)
            {
                if(fixed_values[i][k] == 0)
                {
                    int idx = possibleValues[i][k].back();
                    solution[i][k] = possibleValues[i][k].at(idx);

                    // check if this is the cell we are updating next and if so increment the value to be tried next
                    // and of there are no values to be tried, set it back to the first one and flag that we are
                    // incremeneting the next cell instead
                    if ((i == updatableCells[updatingCellIdx].at(0)) && (k == updatableCells[updatingCellIdx].at(1)))
                    {
                        cout << "Attempt: " << counter << "/" << totalCombinations << endl;
                        counter++;
                        if (idx >= possibleValues[i][k].size()-2)
                        {
                            possibleValues[i][k].pop_back();
                            possibleValues[i][k].push_back(0);
                            updatingCellIdx++;
                            if(updatingCellIdx == updatableCells.size())
                            {
                                cout << "NO SOLUTION FOUND!" << endl;
                                return;
                            }
                        }
                        else
                        {
                            possibleValues[i][k].pop_back();
                            possibleValues[i][k].push_back(++idx);
                        }
                    }
                }
            }
        }
        
    }

}

bool Sudoku::checkValuePossible(int valToCheck, int row, int col)
{
    for(int i = 0; i < NUM_COLS; i++)
    {
        if(values[row][i] == valToCheck)
        {
            return false;
        }
    }

    for(int i = 0; i < NUM_ROWS; i++)
    {
        if(values[i][col] == valToCheck)
        {
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
                        return false;
                    }
                break;

                case 1:
                    if((values[row+1][col+1] == valToCheck) || (values[row+2][col+1] == valToCheck) || (values[row+1][col-1] == valToCheck) || (values[row+2][col-1] == valToCheck))
                    {
                        return false;
                    }
                break;

                case 2:
                    if((values[row+1][col-1] == valToCheck) || (values[row+2][col-1] == valToCheck) || (values[row+1][col-2] == valToCheck) || (values[row+2][col-2] == valToCheck))
                    {
                        return false;
                    }
                break;
            }
        break;

        case 1:
            switch(col%3)
            {
                case 0:
                    if((values[row-1][col+1] == valToCheck) || (values[row-1][col+1] == valToCheck) || (values[row+1][col+2] == valToCheck) || (values[row-1][col+2] == valToCheck))
                    {
                        return false;
                    }
                break;

                case 1:
                    if((values[row-1][col+1] == valToCheck) || (values[row-1][col+1] == valToCheck) || (values[row+1][col-1] == valToCheck) || (values[row-1][col-1] == valToCheck))
                    {
                        return false;
                    }
                break;

                case 2:
                    if((values[row-1][col-1] == valToCheck) || (values[row-1][col-1] == valToCheck) || (values[row+1][col-2] == valToCheck) || (values[row-1][col-2] == valToCheck))
                    {
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
                        return false;
                    }
                break;

                case 1:
                    if((values[row-1][col+1] == valToCheck) || (values[row-2][col+1] == valToCheck) || (values[row-1][col-1] == valToCheck) || (values[row-2][col-1] == valToCheck))
                    {
                        return false;
                    }
                break;

                case 2:
                    if((values[row-1][col-1] == valToCheck) || (values[row-2][col-1] == valToCheck) || (values[row-1][col-2] == valToCheck) || (values[row-2][col-2] == valToCheck))
                    {
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