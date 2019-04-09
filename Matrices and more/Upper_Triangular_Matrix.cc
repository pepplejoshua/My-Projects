#include "Upper_Triangular_Matrix.h"
#include <iostream>

using namespace std;

// Constructor
Upper_Triangular_Matrix::Upper_Triangular_Matrix(int n, double value) : Triangular_Matrix(n, value)
{
    
}

// this returns a constant reference to the constant value in the index equivalent of (i, j)
const double& Upper_Triangular_Matrix::operator()(int i, int j) const
{
    if (i > j)
        return 0;
    const int k = map(i, j);
    return array[k];
}

// this returns a constant reference to the constant value in the index equivalent of (i, j)
double& Upper_Triangular_Matrix::operator()(int i, int j)
{
    if (i > j)
    {
        double var = 0;
        return var;
    }
    const int k = map(i, j);
    return array[k];
}

// this prints the matrix in 2D form
void Upper_Triangular_Matrix::print()
{
    cout << "* Upper Triangular Matrix * \n";
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
double Upper_Triangular_Matrix::ifnform()
{
    double maxS = 0;
    
    for (int i = 0; i < n; ++i)
    {
        double rowSum = 0;
        for (int j = 0; j < n; ++j)
        {
            if (j < i)
            {
                continue;
            }
            else
            {
                rowSum += this->operator()(i, j);
            }
        }
        
        if (rowSum > maxS)
            maxS = rowSum;
    }
    return maxS;
}

// this returns the 1D array index equivalent for a passed in 2D array index (i, j)
const int Upper_Triangular_Matrix::map(int i, int j) const
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

    return i + summation(j);
}


