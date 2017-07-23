// Aidan Lewis
// cell.h

#ifndef CELL_H
#define CELL_H

#include <list>
#include <iostream>

using namespace std;

class cell {
  
  public:
    cell(); // constructor
    ~cell(); // destructor
    int getValue();
    void setValue(int);
    void listRemove(int);
    int listFront();
    int listSize();
    list<int>::const_iterator listBegin();
    list<int>::const_iterator listEnd();
  private:
    list<int> options; // list of possibilities
    int value; // cell value
};

#endif
