#ifndef Lower_Triangular_Matrix_h
#define Lower_Triangular_Matrix_h

#include <stdio.h>
#include "Triangular_Matrix.h"

class Lower_Triangular_Matrix : public Triangular_Matrix
{
public:
    // Constructor
    Lower_Triangular_Matrix(int n, double value = 0.0);
    // Destructor
    ~Lower_Triangular_Matrix() { }
    // this returns a constant reference to the constant value in the index equivalent of (i, j)
    const double& operator()(int i, int j) const;
    // this returns a reference to the value in the index equivalent of (i, j)
    double& operator()(int i, int j);
    // this prints the matrix in 2D form
    void print();
    // this calculates the highest row sum in the matrix
    double ifnform();
    
    // this returns the 1D array index equivalent for a passed in 2D array index (i, j)
    const int map(int i, int j) const;
};
#endif /* Lower_Triangular_Matrix_h */


/* map(int, int) FUNCTION:
 for each 0 < i < n (rows)
 for each 0 < j <= i, (columns), this restricts the number of columns to not exceed the number of rows because of the actual indexes being used to store values, creating the right angled triangle of numbers needed. The formular n ( n + 1 ) / 2 gives the number of necessary storage spaces.
 
 Actual formula used => (col) + summation(row)
 
 if i < j
 k = i + summation(0 + 1 + ... + j) because the number of rows (i) limits the number of columns (j), and array[i, j] == array[j, i]
 else if j <= i
 k = j + summation(0 + 1 + ... + i) which is the regular formula
 
 eg: if i = 2 and j = 3;
 k = 2 + 0 + 1 + 2 + 3 = index 8
 Therefore, position Matrix[2, 3] is mapped to Array[8]
 
 eg: if i = 1 and j = 0;
 k = 0 + 0 + 1 = index 1
 Therefore, position Matrix[1, 0] is mapped to Array[1]
 */

