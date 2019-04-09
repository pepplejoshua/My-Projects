// IMPORTANT: Do not modify the contents of this file
//
// Polynom.h
// Definition of a simple polynomial class of degree n
#ifndef POLYNOM_H
#define POLYNOM_H
#include <vector>
#include <iostream>
using namespace std;
class Polynom {
public:
    // Default constructor.  Polynom()
    //
    // Postcondition: Creates an "empty" polynomial
    
    Polynom();
    
    // Constructor. Polynom(const vector<int>& )
    //
    // Postcondition: Creates a polynomial with coefficients provided in the vector parameter;
    //
    
    Polynom(const vector<int>& coeff);
    
    // Overloaded add operator. operator+(const Polynom& ) const
    //
    // Precondition : Polynomials this and RHS are nonempty
    // Postcondition: The sum of this polynomial and RHS is returned; this polynomial
    //                 and RHS are unchanged
    
    Polynom operator+(const Polynom& RHS) const;
    
    // Overloaded subtract operator. operator-(const Polynom& ) const
    // Precondition : Polynomials this and RHS are nonempty
    // Postcondition: The RHS is subtracted from  this  and the result is returned; this polynomial
    //                 and RHS are unchanged
    
    Polynom operator-(const Polynom& RHS) const;
    
    // Overloaded function evaluation operator()(double x) const
    // Precondition : Polynomials this is nonempty
    // Postcondition: this polynomial is evaluated at x and the the value
    //                is returned; this polynomial is unchanged
    
    double operator()(double x) const;
    
    
    
    // Set the coefficient of x^k.
    // Precondition: k >= 0 and k <= n, where n is the degree of this polynomial
    // Postcondition: If precondition is satisfied the coefficient of x^k is changed to
    //                c and returns true; otherwise no change is made and returns false;
    
    bool  setCoeff(int k, int c);
    
    // Get the coefficient of x^k.
    // Precondition: k >= 0 and k <= n, where n is the degree of this polynomial
    // Postcondition: If precondition is satisfied parameter c is assigned
    //                the coefficient of x^k
    //                and returns true;
    //                otherwise returns false and parameter c remains unchanged
    
    bool  getCoeff(int k, int& c) const;
    
    
    // Stream insertion.
    //
    // Precondition: Polynomial this is nonempty
    // Postcondition: Write the polynomial onto stream sout.
    // Example: if the data member P's content is  [4 0 -1 2 0 0] the output
    //          would be 4x^5 - x^3 + 2x^2
    
    ostream& insert(ostream& sout);
    
    // Stream extraction.
    //
    // Postcondition: Read the coefficients of this polynomial from stream sin
    // Example: if the user entered the following
    //              -1 1 0 0 2 14 0
    //           at the keyboard, this Polynom object will replace data member P's
    //            current content with [ -1 1 0 0 2 14 0]
    
    istream& extract(istream& sin);
    
private:
    vector<int> P;     // coefficients of the polynomial; if P is nonempty and P.size() is n
    // then P[i] is the coefficient
    // of x raised to power (n-i-1)
    
};

// overloaded stream to write the polynomial RHS onto stream Out
ostream& operator<<(ostream& Out, Polynom& RHS);
istream& operator>>(istream& In, Polynom& RHS);

#endif
