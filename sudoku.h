// Aidan Lewis
// sudoku.h

#ifndef SUDOKU_H
#define SUDOKU_H

#include "cell.h"

#include <iostream>
#include <list>
using namespace std;

class sudoku: public cell
{
  public:
    sudoku(); // constructor
    ~sudoku(); // destructor

    // member function
    void checkRow(int, int);
    void checkCol(int, int);
    void checkBox(int, int);
    bool checkAll();
    void print();
    void solve();
    void setBoard(int, int, int);
    void singletonRow(int, int);
    void singletonCol(int, int);
    void singletonBox(int, int);
    void performCheck(int, int);

    // variable
    cell board[9][9];

};

#endif
