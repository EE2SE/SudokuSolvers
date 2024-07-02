#include "../inc/sudoku.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atoi */

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
                    fixed_values[row][column] = (int(val - '0') == 0) ? false : true;
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