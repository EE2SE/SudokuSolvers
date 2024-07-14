#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

#include "../inc/sudoku.hpp"
#include "../inc/sudokuBrute.hpp"
#include "../inc/sudokuBruteBetter.hpp"
#include "../inc/sudokuBacktrackV1.hpp"
#include "../inc/sudokuBacktrackV2.hpp"
#include "../inc/sudokuRecursive.hpp"

#define MAJOR_V 0
#define MINOR_V 3

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;
using chrono::milliseconds;

void extractSudoku(int line)
{
    string filename = "../sudokus/Sudokus_25Digits_10000.txt";
    ifstream inFile;
    ofstream outFile;

    inFile.open("../Sudokus/Sudokus_25Digits_10000.txt");

    outFile.open("../Sudokus/sudokuTest.txt", ios::trunc);

    if (!outFile)
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    string sudokuLine;
    for (int i = 0; i < line; i++)
    {
        inFile >> sudokuLine;
    }

    outFile << sudokuLine;

    inFile.close();
    outFile.close();
}

int main(int argc, char **argv)
{
    cout << "Sudoku Solvers Comparison V" << MAJOR_V << "." << MINOR_V << endl
         << endl;
    ofstream results;
    results.open("../Sudokus/results.txt", ios::trunc);
    string filename = "../Sudokus/sudokuTest.txt";
for (int j = 0; j < 3; j++)
{


    for (int i = 1; i < 30001; i++)
    {
        if(i%1000 == 0)
        {
            cout << i << "/" << 30000 << endl;
        }
        extractSudoku(i);
        SudokuRecursive sudokuRec(filename);
        SudokuBacktrackV1 sudokuBack1(filename);
        SudokuBacktrackV2 sudokuBack2(filename);
        auto t1 = high_resolution_clock::now();
        sudokuRec.solve();
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        results << i << ",";
        results << ms_double.count() << ",";

        t1 = high_resolution_clock::now();
        sudokuBack1.solve();
        t2 = high_resolution_clock::now();
        ms_double = t2 - t1;
        results << ms_double.count() << ",";

        t1 = high_resolution_clock::now();
        sudokuBack2.solve();
        t2 = high_resolution_clock::now();
        ms_double = t2 - t1;
        results << ms_double.count() << "\n";
    }
}
    results.close();

    // cout << "Solving " << filename << endl;
    // SudokuRecursive sudokuRec(filename);
    // auto t1 = high_resolution_clock::now();
    // sudokuRec.solve();
    // auto t2 = high_resolution_clock::now();
    // duration<double, std::milli> ms_double = t2 - t1;
    // cout << ms_double.count() << "ms\n";

    // string filename = "../sudoku_hard.txt";
    // string filename2 = "../sudoku1_simple.txt";
    // SudokuBrute sudokuBase(filename2);
    // SudokuBruteBetter sudokuBrute2(filename2);
    // SudokuBacktrackV1 sudokuBack1(filename, true);
    // SudokuBacktrackV2 sudokuBack2(filename);
    // SudokuRecursive sudokuRec(filename);

    // cout << endl << endl << "Brute Force" << endl;
    // auto t1 = high_resolution_clock::now();
    // // sudokuBase.solve();
    // auto t2 = high_resolution_clock::now();

    // /* Getting number of milliseconds as a double. */
    // duration<double, std::milli> ms_double = t2 - t1;

    // cout << ms_double.count() << "ms\n";

    // cout << endl << endl << "Brute Force Lite" << endl;
    // t1 = high_resolution_clock::now();
    // // sudokuBrute2.solve();
    // t2 = high_resolution_clock::now();
    // ms_double = t2 - t1;
    // cout << ms_double.count() << "ms\n";

    // cout << endl << endl << "Backtrack V1" << endl;
    // t1 = high_resolution_clock::now();
    // sudokuBack1.solve();
    // t2 = high_resolution_clock::now();
    // ms_double = t2 - t1;
    // cout << ms_double.count() << "ms\n";

    // cout << endl << endl << "Backtrack V2" << endl;
    // t1 = high_resolution_clock::now();
    // sudokuBack2.solve();
    // t2 = high_resolution_clock::now();
    // ms_double = t2 - t1;
    // cout << ms_double.count() << "ms\n";

    // cout << endl << endl << "Recursive" << endl;
    // t1 = high_resolution_clock::now();
    // sudokuRec.solve();
    // t2 = high_resolution_clock::now();
    // ms_double = t2 - t1;
    // cout << ms_double.count() << "ms\n";

    return 0;
}
