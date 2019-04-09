/////////////////////////////////////////////////////////////////
//CPSC 2620 Assignment 5
//Problem 2
//Written by: Joshua Pepple
//Date: March 22nd 2017
/////////////////////////////////////////////////////////////////

#include <iostream>
#include "sudokuGrid.h"
#include <fstream>

using namespace std;

bool solve(SudokuGrid& grid, int row, int col, int& count);

int main()
{   
   string name;
   cout << "Enter file name -- ";
   cin >> name;
      
   SudokuGrid grid;
   ifstream input(name);
   int c = 0, row = 1, col = 1;
   input >> grid;
   if(solve(grid,row,col,c))
   {
      cout << grid << endl;
      cout << "Successful!" << endl;
      cout << "Solve function was called " << c << " times."<< endl;
   }
   
   
   else{
      cout << grid << endl;
      cout << "Failed. Can't solve!" << endl;
      cout << "Solve function was called " << c << " times."<< endl;
   }
   
   return 0;    
   
}


bool solve(SudokuGrid& grid, int row, int col, int& count)
{
   if(!grid.find())
      return true;
   
   if (!grid.empty(row, col))
   {
      if(col == 9)
      {
	 col = 1;
	 row++;
	 return(solve(grid,row,col,count));
      }
      else
      {
	 col++;
	 return(solve(grid, row, col, count));
      }
   }
   
   for(int num = 1; num <= 9; num++)
   {
      ++count;
      if(grid.isValid(row,col,num))
      {
	 grid.put(row,col,num);
	 
	 if(solve(grid,row,col,count))
	    return true;
	 
	 grid.clear(row,col);
      }
   }
   return false;
}




  
