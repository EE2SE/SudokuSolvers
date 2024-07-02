#include <sudoku.hpp>
#include <iostream>

using namespace std;

Sudoku::Sudoku()
{
    cout<<"Please provide a text file"<<endl;
}

Sudoku::Sudoku(string filename)
{

}

class Sudoku
{
    public:
        Sudoku(string filename);
        Sudoku();
        bool solve();
        void readInValues();
        void printSolution();

    private:
        bool solved;
        int values[9][9];
        bool fixed_values[9][9];
};
