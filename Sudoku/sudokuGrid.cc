//
// Assignment 5
//
// SudokuGrid class
//
// Howard Cheng
// November 4, 2013
//
// This class implements a Sudoku puzzle grid.
//
// All valid coordinates are from 1 to 9 (row and column).  Invalid
// coordinates will generate an assertion failure.
//

#include "sudokuGrid.h"
#include <cassert>
#include <algorithm>
#include <cctype>

using namespace std;

// constructs an empty puzzle (no cells filled)
SudokuGrid::SudokuGrid()
{
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      grid[i][j] = EMPTY;
    }
  }
}

// check if the cell at the specified coordinates is empty
bool SudokuGrid::empty(int row, int col) const
{
  return grid[row-1][col-1] == EMPTY;
}

// check to see if it is valid to put the specified value at the specified
// location.
bool SudokuGrid::isValid(int row, int col, int val) const
{
  assert(1 <= row && row <= 9);
  assert(1 <= col && col <= 9);
  assert(1 <= val && val <= 9);

  // check row
  for (int j = 0; j < SIZE; j++) {
    if (j != col-1 && val == grid[row-1][j]) {
      return false;
    }
  }

  // check column
  for (int i = 0; i < SIZE; i++) {
    if (i != row-1 && val == grid[i][col-1]) {
      return false;
    }
  }

  // check the 3x3 box
  int boxr = (row-1) / 3 * 3;  // coordinates of the top left cell of the box
  int boxc = (col-1) / 3 * 3;
  for (int i = boxr; i < boxr+SIZE/3; i++) {
    for (int j = boxc; j < boxc+SIZE/3; j++) {
      if ((i != row-1 || j != col-1) && val == grid[i][j]) {
	return false;
      }
    }
  }

  // none of the checks found anything wrong
  return true;
}

// check to see if the entire grid is valid (based on what has been filled
// so far)
bool SudokuGrid::isValid() const
{
  bool used[SIZE+1];     // which digits have been used

  // check each row to check for duplicates
  for (int i = 0; i < SIZE; i++) {
    fill(used+1, used+SIZE+1, false);
    for (int j = 0; j < SIZE; j++) {
      if (grid[i][j] != EMPTY && used[grid[i][j]]) {
	return false;
      }
      used[grid[i][j]] = true;
    }
  }

  // check each column to check for duplicates
  for (int j = 0; j < SIZE; j++) {
    fill(used+1, used+SIZE+1, false);
    for (int i = 0; i < SIZE; i++) {
      if (grid[i][j] != EMPTY && used[grid[i][j]]) {
	return false;
      }
      used[grid[i][j]] = true;
    }
  }

  // check each 3x3 box to check for duplicates
  for (int bi = 0; bi < SIZE; bi += SIZE/3) {
    for (int bj = 0; bj < SIZE; bj += SIZE/3) {
      fill(used+1, used+SIZE+1, false);
      for (int i = 0; i < SIZE/3; i++) {
	for (int j = 0; j < SIZE/3; j++) {
	  if (grid[bi+i][bj+j] != EMPTY && used[grid[bi+i][bj+j]]) {
	    return false;
	  }
	  used[grid[bi+i][bj+j]] = true;
	}
      }
    }
  }

  // no duplicates constraints are violated, so it must be okay (because
  // every cell is either empty or 1-9).
  return true;
}

//search for empty space in grid
bool SudokuGrid::find()
{
   for(int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
	 if(grid[i][j] == EMPTY)
	    return true;
   return false;
}

// fill the cell at the specified coordinates to be val (must be 1-9)
// any previous value is overwritten.  There is NO CHECK on whether
// it is legal.
void SudokuGrid::put(int row, int col, int val)
{
  assert(1 <= row && row <= 9);
  assert(1 <= col && col <= 9);
  assert(1 <= val && val <= 9);

  grid[row-1][col-1] = val;
}
  
// clear a particular cell
void SudokuGrid::clear(int row, int col)
{
  assert(1 <= row && row <= 9);
  assert(1 <= col && col <= 9);

  grid[row-1][col-1] = EMPTY;
}

// clear the entire grid
void SudokuGrid::clear()
{
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      grid[i][j] = EMPTY;
    }
  }
}

// For input, it will simply read the next 81 non-space characters, and
// put the digits into the grid one row at a time.  The characters must
// be '1', '2', ..., '9', or '.' (empty).  An assertion failure will
// be generated for bad input files.  It DOES NOT, however, check whether
// the grid is valid.
istream& operator>>(istream& is, SudokuGrid& sgrid)
{
  char c;
  for (int i = 0; i < SudokuGrid::SIZE; i++)
  {
     for (int j = 0; j < SudokuGrid::SIZE; j++)
     {
	is >> c;
	assert((isdigit(c) && c != '0') || c == '.');
	sgrid.grid[i][j] = (isdigit(c)) ? c - '0' : SudokuGrid::EMPTY;
     }
  }
  return is;
}

// output operator
ostream& operator<<(ostream& os, const SudokuGrid& sgrid)
{
  for (int i = 0; i < SudokuGrid::SIZE; i++) {
    if (i > 0 && i % (SudokuGrid::SIZE/3) == 0) {
      os << "---+---+---" << endl;
    }
    for (int j = 0; j < SudokuGrid::SIZE; j++) {
      if (j > 0 && j % (SudokuGrid::SIZE/3) == 0) {
	os << "|";
      }
      os << static_cast<char>(sgrid.grid[i][j]+'0');
    }
    os << endl;
  }
  return os;
}
