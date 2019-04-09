#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    
    matrix a, b, c, d;
    
    // read matrix 1 and print
    a.read();
    cout << "\nMatrix a \n"; a.write();

    // read matrix 2 and print
    b.read();
    cout << "\nMatrix b \n"; b.write();

    // read matrix 3 and print
    c.read();
    cout << "\nMatrix c \n"; c.write();

    // set d to a and change first column to 0 and print d
    int nr = 0, nc = 0;
    a.getDimensions(nr, nc);
    for (int i = 0; i < nr; ++i)
    {
        for (int j = 1; j < nc; ++j)
        {
            d.element(i, j) = a.element(i, j);
            
        }
    }
    cout << "\nMatrix d \n"; d.write();
    
    // a + b
    cout << "Problem 1: a + b => \n";
    a.add(b);
    a.write();

    // a * c - a
    matrix save = a.multiply(c);
    save.subtract(a);
    cout << "Problem 2: a x c - a => \n";
    save.write();

    // (a + d) * c
    a.add(d);
    matrix store = a.multiply(c);
    cout << "Problem 3: (a + d) * c => \n";
    store.write();
    return 0;
}
