// Aidan Lewis
// cell.cpp

#include "cell.h"

#include <iostream>
#include <list>

using namespace std;

// constructor
cell::cell()
{
  for (int i = 9; i > 0; i--)
  {
    options.push_back(i); // add 9 options for cell
  }
  value = 0; // set value to 0 initially (unsolved)
}

// destructor
cell::~cell()
{ }

// return value
int cell::getValue()
{
  return value;
}

// set value
void cell::setValue(int val)
{
  value = val;
}

void cell::listRemove(int val)
{
  options.remove(val);
}

int cell::listFront()
{
  return options.front();
}

int cell::listSize()
{
  return options.size();
}

list<int>::const_iterator cell::listBegin()
{
  return options.begin();
}

list<int>::const_iterator cell::listEnd()
{
  return options.end();
}





