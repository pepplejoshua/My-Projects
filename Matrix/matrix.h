#ifndef matrix_h
#define matrix_h

#include <stdio.h>

class matrix {

public:
    matrix(int m = 2, int n = 2);
    //~matrix();
    void getDimensions(int &m, int &n) const;
    int& element(const int i, const int j);
    const int& element(const int i, const int j) const;
    
    void add(const matrix operand);
    void subtract(const matrix operand);
    matrix multiply(const matrix B) const;
    
    void read();
    void write() const;
    
    
private:
    void deallocate();
    int **matrixArray;
    int rows, cols;
};

#endif /* matrix_hpp */
