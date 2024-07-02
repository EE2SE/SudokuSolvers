#include "../inc/sudoku.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atoi */
#include <map>

using namespace std;

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

    int emptySpaces = NUM_COLS*NUM_ROWS - filledSpaces;

    // initialise a 3D vector storing all non-taken values
     vector< vector< vector<int> > > possibleValues;
    for (int i = 0; i < NUM_ROWS; i++)
    {
        possibleValues.push_back(vector<vector<int>>());
        for(int k = 0; k< NUM_COLS; k++)
        {
            possibleValues[i].push_back(vector<int>());
            if(fixed_values[i][k] == 0)
            {
                for(int checkval = 0; checkval < 8; checkval)
                {
                    possibleValues[i][k]
                }
                
            }
        }
    }

}

bool Sudoku::checkValuePossible()
{
    
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