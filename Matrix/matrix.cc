#include "matrix.h"
#include <assert.h>
#include <iostream>

using namespace std;

matrix::matrix(int m, int n)
{
     rows = m;
     cols = n;
    
    matrixArray = new int*[rows];
    
    for (int i = 0; i < rows; ++i)
    {
        matrixArray[i] = new int[cols];
    }
    
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; j++)
        {
            matrixArray[i][j] = 0;
        }
    }
}

//matrix::~matrix()
//{
//    deallocate();
//}

void matrix::getDimensions(int &m, int &n) const
{
    m = rows;
    n = cols;
}

int& matrix::element(const int i, const int j)
{
    assert(i >= 0 && i < rows);
    assert(j >= 0 && j < cols);
    
    return matrixArray[i][j];
}

const int& matrix::element(const int i, const int j) const
{
    assert(i >= 0 && i < rows);
    assert(j >= 0 && j < cols);
    
    return matrixArray[i][j];
}

void matrix::add(const matrix operand)
{
    int sRows, sCols;
    sRows = sCols = 0;
    operand.getDimensions(sRows, sCols);
    
    assert(sRows ==  rows && sCols ==  cols);
    
    int **newMatrix = new int*[sRows];
    
    for (int i = 0; i < sRows; ++i)
    {
        newMatrix[i] = new int[sCols];
    }
    
    for (int i = 0; i < sRows; ++i)
    {
        for (int j = 0; j < sCols; ++j)
        {
            int value =  matrixArray[i][j] + operand.element(i, j);
            newMatrix[i][j] = value;
        }
    }
    
    for (int i = 0; i < sRows; ++i)
    {
        for (int j = 0; j < sCols; ++j)
        {
             matrixArray[i][j] = newMatrix[i][j];
        }
    }
    
    for(int i = 0; i <  rows; ++i)
    {
        delete [] newMatrix[i];
    }
    delete []newMatrix;
}

void matrix::subtract(const matrix operand)
{
    int sRows, sCols;
    sRows = sCols = 0;
    operand.getDimensions(sRows, sCols);
    
    assert(sRows ==  rows && sCols ==  cols);
    
    int **newMatrix = new int*[sRows];
    
    for (int i = 0; i < sRows; ++i)
    {
        newMatrix[i] = new int[sCols];
    }
    
    for (int i = 0; i < sRows; ++i)
    {
        for (int j = 0; j < sCols; ++j)
        {
            int value =  matrixArray[i][j] - operand.element(i, j);
            newMatrix[i][j] = value;
        }
    }
    
    for (int i = 0; i < sRows; ++i)
    {
        for (int j = 0; j < sCols; ++j)
        {
             matrixArray[i][j] = newMatrix[i][j];
        }
    }
    
    for(int i = 0; i <  rows; ++i)
    {
        delete [] newMatrix[i];
    }
    delete []newMatrix;
    newMatrix = nullptr;
}

matrix matrix::multiply(const matrix B) const
{
    int m, n;
    B.getDimensions(m, n);
    assert(m == cols);
    
    matrix mult(rows, n);
    int a, b, i, j, x, y, sum = 0;
    a = b = i = j = x = y = 0;
    
    while (true)
    {
        sum += matrixArray[i][j] * B.element(a, b);
        a++;
        j++;
        
        if (j == cols)
        {
            j = 0;
            a = 0;
            b++;
            mult.element(x, y) = sum;
            if(y + 1 == n)
            {
                y = 0;
                x++;
            }
            else
                y++;
            sum = 0;
        }
        if (b == n)
        {
            b = 0;
            i++;
        }
        if (i == rows)
            break;
    }
    return mult;
}

void matrix::read()
{
    int m = 0, n = 0;
    cout << "Enter new number of rows and columns -- ";
    cin >> m >> n;
    
    assert(m > 0 && n > 0);
    deallocate();
    
    matrixArray = new int*[m];
    rows = m;
    cols = n;
    for (int i = 0; i < m; ++i)
    {
        matrixArray[i] = new int[n];
    }
    
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            int value = 0;
            cout << "Enter number -- ";
            cin >> value;
            matrixArray[i][j] = value;
        }
    }
}

void matrix::write() const
{
    cout << endl;
    for(int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << element(i, j) << " ";
            if (j + 1 == cols)
                cout << endl;
        }
    }
    cout << endl;
}

void matrix::deallocate()
{
    for(int i = 0; i < rows; ++i)
    {
        delete [] matrixArray[i];
    }
    delete [] this->matrixArray;
    this->matrixArray = nullptr;
}
