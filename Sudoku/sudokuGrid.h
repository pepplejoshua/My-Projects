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

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <iostream>

using namespace std;

class SudokuGrid {
public:
  // number of rows and columns, use SudokuGrid::SIZE to access.
  static const int SIZE = 9;

  // constructs an empty puzzle (no cells filled)
  SudokuGrid();

  // check if the cell at the specified coordinates is empty
  bool empty(int row, int col) const;

  // check to see if it is valid to put the specified value at the specified
  // location by checking whether it will violate any constraint.  Value
  // must be 1-9.
  bool isValid(int row, int col, int val) const;

  // check to see if the entire grid is valid (based on what has been filled
  // so far).
  bool isValid() const;

  bool find();
  

  // fill the cell at the specified coordinates to be val (must be 1-9)
  // any previous value is overwritten.  There is NO CHECK on whether
  // it is legal.
  void put(int row, int col, int val);
  
  // clear a particular cell
  void clear(int row, int col);

  // clear the entire grid
  void clear();

  // input and output operators
  //
  // For input, it will simply read the next 81 non-space characters, and
  // put the digits into the grid one row at a time.  The characters must
  // be '1', '2', ..., '9', or '.' (empty).  An assertion failure will
  // be generated for bad input files.  It DOES NOT, however, check whether
  // the grid is valid.
  friend istream& operator>>(istream& is, SudokuGrid& sgrid);
  friend ostream& operator<<(ostream& os, const SudokuGrid& sgrid);

private:
  static const int EMPTY = 0;   // 0 to indicate empty cell
  int grid[SIZE][SIZE];
};


#endif
