#include <fstream> 
#include <iostream>
#include <string>
#include <chrono>

#include "sudoku.hpp"

#define MAJOR_V 0
#define MINOR_V 1

using namespace std;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

int main(int argc,  char** argv) 
{
    cout << "Sudoku Solvers Comparison V" << MAJOR_V << "." << MINOR_V << endl << endl;
    string filename = "sudoku1_simple.txt";
    Sudoku mysudoku(filename);



    auto t1 = high_resolution_clock::now();
    (void)mysudoku.solveBruteForce();
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    cout << ms_int.count() << "ms\n";
    cout << ms_double.count() << "ms\n";
    return 0;
}


