#include <fstream> 
#include <iostream>
#include <string>
#include <sudoku.hpp>

using namespace std;


int main(int argc,  char** argv) 
{
    string filename = "sudoku1.txt";
    Sudoku mysudoku(filename);

    return 0;
}


