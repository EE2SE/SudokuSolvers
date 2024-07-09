#include <fstream> 
#include <iostream>
#include <string>
#include <chrono>

#include "../inc/sudoku.hpp"
#include "../inc/sudokuBrute.hpp"
#include "../inc/sudokuBruteBetter.hpp"
#include "../inc/sudokuBacktrackV1.hpp"    
#include "../inc/sudokuBacktrackV2.hpp"  

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
    string filename = "../sudoku_hard.txt";
    SudokuBrute sudokuBase(filename);
    SudokuBruteBetter sudokuBrute2(filename);
    SudokuBacktrackV1 sudokuBack1(filename);
    SudokuBacktrackV2 sudokuBack2(filename);

    cout << endl << endl << "Brute Force" << endl;
    auto t1 = high_resolution_clock::now();
    // sudokuBase.solve();
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    cout << ms_double.count() << "ms\n";

    cout << endl << endl << "Brute Force Lite" << endl;
    t1 = high_resolution_clock::now();
    // sudokuBrute2.solve();
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    cout << ms_double.count() << "ms\n";

    cout << endl << endl << "Backtrack V1" << endl;
    t1 = high_resolution_clock::now();
    sudokuBack1.solve();
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    cout << ms_double.count() << "ms\n";

    cout << endl << endl << "Backtrack V2" << endl;
    t1 = high_resolution_clock::now();
    sudokuBack2.solve();
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    cout << ms_double.count() << "ms\n";
   

    return 0;
}


