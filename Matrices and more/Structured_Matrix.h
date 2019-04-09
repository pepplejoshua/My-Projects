#ifndef Structured_Matrix_h
#define Structured_Matrix_h

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class Structured_Matrix
{
public:
    // Constructor
    Structured_Matrix(int n, double value = 0.0) {
        this->n = n;
        arraySize = (n * (n + 1)) / 2;
        vector <double> newArray(arraySize, value);
        array = newArray;
    }
    // Destructor
    virtual ~Structured_Matrix() { }
    // this returns a constant reference to the constant value in the index equivalent of (i, j)
    virtual const double& operator()(int i, int j) const = 0;
    // this returns a reference to the value in the index equivalent of (i, j)
    virtual double& operator()(int i, int j) = 0;
    // this prints the matrix in 2D form
    virtual void print() = 0;
    // this calculates the highest row sum in the matrix
    virtual double ifnform() = 0;
    
protected:
    // this returns the 1D array index equivalent for a passed in 2D array index (i, j)
    virtual const int map(int i, int j) const = 0;
    
    // this returns (0 + 1 + ... + n)
    const int summation(int i) const
    {
        int sum = 0;
        for (int c = 0; c <= i; ++c)
        {
            sum += c;
        }
        return sum;
    }
    
    // this is our one dimensional vector
    vector <double> array;
    // this is the calculated size for 'array' i.e, n (n + 1) / 2
    int arraySize;
    // this is the value the user passed in to initialize an n x n array
    int n;
};
#endif /* Structured_Matrix_h */


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

