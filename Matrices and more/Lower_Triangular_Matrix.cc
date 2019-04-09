#include "Lower_Triangular_Matrix.h"
#include <iostream>

using namespace std;

// This initializes a Lower Triangular Matrix by Initialize up the chain of inheritance
Lower_Triangular_Matrix::Lower_Triangular_Matrix(int n, double value) : Triangular_Matrix(n, value)
{
    
}

// this returns a constant reference to an index from a constant Matrix
const double& Lower_Triangular_Matrix::operator()(int i, int j) const
{
    if (i < j)
        return 0;
    const int k = map(i, j);
    return array[k];
}

// this returns a reference to an index from a constant Matrix and therefore allows it to be changed
double& Lower_Triangular_Matrix::operator()(int i, int j)
{
    if (i < j)
    {
        double var = 0;
        return var;
    }
    const int k = map(i, j);
    return array[k];
}

// this prints the matrix in 2D form
void Lower_Triangular_Matrix::print()
{
    cout << "* Lower Triangular Matrix * \n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << this->operator()(i, j) << " ";
        }
        cout << endl;
    }
}

// this calculates the highest row sum in the matrix
double Lower_Triangular_Matrix::ifnform()
{
    double maxS = 0;
    
    for (int i = 0; i < n; ++i)
    {
        double rowSum = 0;
        for (int j = 0; j < n; ++j)
        {
            rowSum += this->operator()(i, j);
        }
        
        if (rowSum > maxS)
            maxS = rowSum;
    }
    return maxS;
}

// this returns the 1D array index equivalent for a passed in 2D array index (i, j)
const int Lower_Triangular_Matrix::map(int i, int j) const
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
    
    return j + summation(i);
}
