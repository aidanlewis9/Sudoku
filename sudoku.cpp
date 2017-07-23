// Aidan Lewis
// sudoku.cpp

#include <iostream>
#include <list>
#include <iterator>

#include "cell.h"
#include "sudoku.h"

using namespace std;

// constructor
sudoku::sudoku() : cell()
{ }

// destructor
sudoku::~sudoku()
{ }

void sudoku::checkRow(int cellI, int cellJ)
{
  for (int i = 0; i < 9; i++)
  {
    // get each value in row and remove from origin cell's options
    int check = board[i][cellJ].getValue();
    board[cellI][cellJ].listRemove(check); 
  }
}

void sudoku::checkCol(int cellI, int cellJ)
{
  for (int j = 0; j < 9; j++)
  {
    // get each value in column and remove from origin cell's options
    int check = board[cellI][j].getValue();
    board[cellI][cellJ].listRemove(check);
  }
}

void sudoku::checkBox(int cellI, int cellJ)
{
  // find start - top-left corner of box
  int startI = (cellI/3)*3;
  int startJ = (cellJ/3)*3;
  // get each value in box and remove from origin cell's options
  for (int a = startI; a < startI + 3; a++)
  {
    for (int b = startJ; b < startJ + 3; b++)
    {
      int check = board[a][b].getValue();
      board[cellI][cellJ].listRemove(check); 
    }
  }
}

bool sudoku::checkAll()
{
  bool solved = true;
  // Loop through the entire board
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (board[i][j].getValue() == 0)
      {
  // if there is aan unsolved cell (value of 0)
	solved = false; // puzzle is not solved
	performCheck(i, j); // check with single possibility and singleton
      }
    }
  }
  return solved;
}

void sudoku::print()
{
  cout << endl;
  for (int j = 0; j < 9; j++)
  {
    for (int i = 0; i < 9; i++)
    {
      cout << board[i][j].getValue() << " ";
    }
    cout << endl;
  }
}

void sudoku::solve()
{
  bool gameOver = false;
  print(); // print board at beginning of game
  while (!gameOver)
  {
    gameOver = checkAll(); // determine if solved or not
    // loop will break if puzzle is solved (game is over then)
  }
  cout << endl << "Puzzle Solved!" << endl;
  print(); // print board at end of game
}

void sudoku::setBoard(int i, int j, int val)
{
  board[i][j].setValue(val); // set up the board
}

void sudoku::singletonRow(int cellI, int cellJ)
{
  list<int>::const_iterator iterator1;
  // iterate through cell's options
  for (iterator1 = board[cellI][cellJ].listBegin(); iterator1 != board[cellI][cellJ].listEnd(); ++iterator1)
  {
    int start = cellI + 1;
    if (start == 9) { start = 0; } // to prevent index issues
    bool match = false;
    // until a match is found or the row has been looped through
    while (start != cellI && match != true)
    {
      list<int>::const_iterator iterator2;
      if (board[start][cellJ].getValue() == 0) // if the cell is unsolved
      {
      // check cell's options to compare them
	for (iterator2 = board[start][cellJ].listBegin(); iterator2 != board[start][cellJ].listEnd(); ++iterator2)
	{
	  // if the two options match
	  if (*iterator1 == *iterator2)
	  {
	    match = true;
	    break;
	  }
	}
	if (match == true) { break; }
      }
      if (start == 8) { start = 0; }
      else { start++; }
    }
  // if no match is found, this must be the cell's value
    if (match == false)
    {
      board[cellI][cellJ].setValue(*iterator1);
      break;
    }
  }
}

void sudoku::singletonCol(int cellI, int cellJ)
{
  list<int>::const_iterator iterator1;
  // iterate through cell's options
  for (iterator1 = board[cellI][cellJ].listBegin(); iterator1 != board[cellI][cellJ].listEnd(); ++iterator1)
  {
    int start = cellJ + 1;
    if (start == 9) { start = 0; } // to prevent index errors
    bool match = false;
    // until a match is found or the row has been looped through
    while (start != cellJ && match != true)
    {
      list<int>::const_iterator iterator2;
      if (board[cellI][start].getValue() == 0) // if the cell is currently unsolved
      {
      // check cell's options to compare them
	for (iterator2 = board[cellI][start].listBegin(); iterator2 != board[cellI][start].listEnd(); ++iterator2)
	{
	// if the two options match
	  if (*iterator1 == *iterator2)
	  {
	    match = true;
	    break;
	  }
	}
	if (match == true) { break; }
      }
      if (start == 8) { start = 0; }
      else { start++; }
    }
  // if no match is found, this must be the cell's value
    if (match == false)
    {
      board[cellI][cellJ].setValue(*iterator1);
      break;
    }
  }
}

void sudoku::singletonBox(int cellI, int cellJ)
{
  list<int>::const_iterator iterator1;
  // iterate through cell's options
  for (iterator1 = board[cellI][cellJ].listBegin(); iterator1 != board[cellI][cellJ].listEnd(); ++iterator1)
  {
    int startI = (cellI/3)*3;
    int startJ = (cellJ/3)*3;
    bool match = false;
    // loop through the box
    for (int i = startI; i < startI + 3; i++)
    {
      for (int j = startJ; j < startJ + 3; j++)
      {
      // if the cell is not the origin cell, and has no value yet
	if ((i != cellI || j != cellJ) && (board[i][j].getValue() == 0))
	{
	  list<int>::const_iterator iterator2;
	  // iterate through options for other cell
	  for (iterator2 = board[i][j].listBegin(); iterator2 != board[i][j].listEnd(); ++iterator2)
	  {
	  // if the two options match
	    if (*iterator1 == *iterator2)
	    {
	      match = true;
	      break;
	    }
	  }
	  if (match == true) { break; }
	}
      }
      if (match == true) { break; }
    }
    // if no match is found, this must be the cell's value
    if (match == false)
    {
      board[cellI][cellJ].setValue(*iterator1);
      break;
    }
  }
}

// call functions to check by single possibility and singleton
void sudoku::performCheck(int i, int j)
{
  checkRow(i, j); 
  checkCol(i, j);
  checkBox(i, j);
  if (board[i][j].listSize() == 1) // if only one possibility remains
  {
    int val = board[i][j].listFront();
    board[i][j].setValue(val); // set this sole value on the board
    return; // no need for singleton, since the cell has been solved
  }
  singletonRow(i, j);
  if (board[i][j].getValue()) // if value is no longer zero, return
  { return; }
  singletonCol(i, j);
  if (board[i][j].getValue()) // if value is no longer zero, return
  { return; }
  singletonBox(i, j);
  if (board[i][j].getValue()) // if value is no longer zero, return
  { return; }
}



