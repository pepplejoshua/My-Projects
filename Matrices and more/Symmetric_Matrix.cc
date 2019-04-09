#include "Symmetric_Matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

// Constructor
Symmetric_Matrix::Symmetric_Matrix(int n, double value) : Structured_Matrix(n, value)
{
}

// this returns a constant reference to the constant value in the index equivalent of (i, j)
const double& Symmetric_Matrix::operator()(int i, int j) const
{
    const int k = map(i, j);
    return array[k];
}

// this returns a reference to the value in the index equivalent of (i, j)
double& Symmetric_Matrix::operator()(int i, int j)
{
    int k = map(i, j);
    return array[k];
}

// this prints the matrix in 2D form
void Symmetric_Matrix::print()
{
    cout << "* Symmetric Matrix * \n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (j <= i)
            {
                int k = map(i, j);
                cout << array[k] << " ";
            }
            else
            {
                int k = map(j, i);
                cout << array[k] << " ";
            }
        }
        cout << endl;
    }
}

// this calculates the highest row sum in the matrix
double Symmetric_Matrix::ifnform()
{
    double maxS = 0;
    
    for (int i = 0; i < n; ++i)
    {
        double rowSum = 0;
        for (int j = 0; j < n; ++j)
        {
            if (j <= i)
            {
                double value = array[map(i, j)];
                rowSum += abs(value);
            }
            else
            {
                double value = array[map(j, i)];
                rowSum += abs(value);
            }
        }
        
        if (rowSum > maxS)
            maxS = rowSum;
    }
    return maxS;
}

// this returns the 1D array index equivalent for a passed in 2D array index (i, j)
const int Symmetric_Matrix::map(int i, int j) const
{
    if (j < 0 && j >= n)
    {
        cout << "Invalid index (j)\n";
        return -1;
    }
    else if (i < 0 && i >= n)
    {
        cout << "Invalid index (i)\n";
        return -1;
    }
    
    if (i < j)
        return i + summation(j);
    else
        return j + summation(i);
    }
