#include <sudoku.hpp>
#include <iostream>
#include <fstream>

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
    string mystring;
    myfile.open(sudoku_filename);
    if ( myfile.is_open() ) { // always check whether the file is open
        myfile >> mystring; // pipe file's content into stream
        cout << mystring; // pipe stream's content to standard output
    }

}