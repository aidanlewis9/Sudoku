#include "cell.h"
#include "sudoku.h"

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <iterator>

using namespace std;

int main()
{
  sudoku game; // instantiate sudoku object

  ifstream ifs;
  string filename;
  // ask user for file
  cout << "Enter the filename of the sudoku puzzle: " << endl;
  cin >> filename;
  ifstream read(filename);
  int num;
  // loop through entire board
  for (int j = 0; j < 9; j++)
  {
    for (int i = 0; i < 9; i++)
    {
      read >> num;
      game.setBoard(i, j, num); // set spot to read number
    }
  }

  game.solve(); // solve puzzle
}
