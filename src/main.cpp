#include <fstream> 
#include <iostream>
#include <string>
#include <chrono>

#include "../inc/sudoku.hpp"
#include "../inc/sudokuBrute.hpp"
#include "../inc/sudokuBruteBetter.hpp"

#define MAJOR_V 0
#define MINOR_V 2

using namespace std;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

int main(int argc,  char** argv) 
{
    cout << "Sudoku Solvers Comparison V" << MAJOR_V << "." << MINOR_V << endl << endl;
    string filename = "../sudoku1_simple.txt";
    SudokuBrute sudokuBase(filename);
    SudokuBruteBetter sudokuBrute2(filename);

    auto t1 = high_resolution_clock::now();
    sudokuBase.solve();
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    cout << ms_double.count() << "ms\n";

    t1 = high_resolution_clock::now();
    sudokuBrute2.solve();
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    cout << ms_double.count() << "ms\n";

    return 0;
}


