#include <fstream> 
#include <iostream>
#include <string>
#include "../inc/sudoku.hpp"

#define MAJOR_V 0
#define MINOR_V 1

using namespace std;


int main(int argc,  char** argv) 
{
    cout << "Sudoku Solvers Comparison V" << MAJOR_V << "." << MINOR_V << endl << endl;
    string filename = "sudoku1.txt";
    Sudoku mysudoku(filename);
    cout << endl << endl;
    mysudoku.printSolution();
    return 0;
}


