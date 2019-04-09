//
//  Polynom.cpp
//  Polynom
//
// Polynom.cpp
// Implementation of a simple polynomial class of degree n


#include <stdio.h>
#include <iostream>
#include "Polynom.h"
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

Polynom::Polynom()
{
    P.clear();
}

Polynom::Polynom(const vector<int>& coeff)
{
    for (int i = 0; i < coeff.size(); ++i)
    {
        P.push_back(coeff[i]);
    }
}

Polynom Polynom::operator+(const Polynom &RHS) const
{
    Polynom pn;
    if (!(this->P.empty()) && !RHS.P.empty())
    {
        
        int firstLength = (int) this->P.size()-1;
        int secLength = (int) RHS.P.size()-1;
        
        for (int i = firstLength; i >= 0; --i)
        {
            if (secLength >= 0)
            {
                int top = P[i];
                int bottom = RHS.P[secLength];
                
                int value = top + bottom;
                
                pn.P.push_back(value);
                
                secLength--;
            }
            else
            {
                pn.P.push_back(P[i]);
            }
        }
        if (secLength >= 0)
        {
            for(int i = secLength; i >= 0; --i)
            {
                pn.P.push_back(RHS.P[i]);
            }
        }
        reverse(pn.P.begin(), pn.P.end());
        return pn;
    }
    return pn;
}

Polynom Polynom::operator-(const Polynom &RHS) const
{
    Polynom pn;
    if (!(this->P.empty()) && !RHS.P.empty())
    {
        
        int firstLength = (int) this->P.size()-1;
        int secLength = (int) RHS.P.size()-1;
        
        for (int i = firstLength; i >= 0; --i)
        {
            if (secLength >= 0)
            {
                int top = P[i];
                int bottom = RHS.P[secLength];
                
                int value = top - bottom;
                
                pn.P.push_back(value);
                
                secLength--;
            }
            else
            {
                pn.P.push_back(P[i]);
            }
        }
        if (secLength >= 0)
        {
            for(int i = secLength; i >= 0; --i)
            {
                pn.P.push_back(0 - (RHS.P[i]));
            }
        }
        reverse(pn.P.begin(), pn.P.end());
        return pn;
    }
    return pn;
}

double Polynom::operator()(double x) const
{
    double result = 0;
    if (!this->P.empty())
    {
        int degree = (int) P.size()-1;
        
        for (int i : P)
        {
            result += i * pow(x, degree);
            degree--;
        }
    }
    return result;
}

bool Polynom::setCoeff(int k, int c)
{
    int deg = (int) P.size()-1;
    
    if (k >= 0 && k <= deg)
    {
        int currDeg = deg;
        for (int i = 0; i <= deg; ++i)
        {
            if (currDeg == k)
            {
                P[i] = c;
                return true;
            }
            currDeg--;
        }
    }
    return false;
}

bool Polynom::getCoeff(int k, int& c) const
{
    int deg = (int) P.size()-1;
    
    if (k >= 0 && k <= deg)
    {
        int currDeg = deg;
        for (int i = 0; i <= deg; ++i)
        {
            if (currDeg == k)
            {
                c = P[i];
                return true;
            }
            currDeg--;
        }
    }
    return false;
}

ostream& Polynom::insert(ostream &sout)
{
    if (!this->P.empty())
    {
        int powerCounter = (int) P.size()-1;
        
        string out;
        
        if (powerCounter == 0)
        {
            cout << to_string(P[0]);
            return sout;
        }
        for (int i = 0; i < P.size(); ++i)
        {
            int num = P[i];
            
            if (num == 0)
            {
                powerCounter--;
            }
            else
            {
                string numInString = to_string(num);
                string powerInString = to_string(powerCounter);
                if (num > 0)
                {
                    if (num == 1)
                    {
                        if (out.length() < 1)
                            out += "x^" + powerInString + " ";
                        else if (powerCounter == 0)
                            out += "+ 1";
                        else if (powerCounter == 1)
                            out += "+ x ";
                        else
                            out += "+ x^" + powerInString + " ";
                    }
                    else
                    {
                        if (out.length() < 1)
                            out += numInString + "x^" + powerInString + " ";
                        else if (powerCounter == 0)
                            out += "+ " + numInString;
                        else if (powerCounter == 1)
                            out += "+ " + numInString + "x ";
                        else
                            out += "+ " + numInString + "x^" + powerInString + " ";
                    }
                }

                else if (num < 0)
                {
                    if (num == -1)
                    {
                        if (out.length() < 1)
                            out += numInString + "x^" + powerInString + " ";
                        else if (powerCounter == 1)
                            out += "- x ";
                        else
                            out += "- x^" + powerInString + " ";
                    }
                    else
                    {
                        if (out.length() < 1)
                            out += numInString + "x^" + powerInString + " ";
                        else if (powerCounter == 0)
                            out += "- " + to_string(abs(num));
                        else if (powerCounter == 1)
                            out += "- " + to_string(abs(num)) + "x ";
                        else
                        {
                            numInString = to_string(abs(num));
                            out += "- " + numInString + "x^" + powerInString + " ";
                        }
                    }
                }
                powerCounter--;
            }
        }
        sout << out;
    }
    else
    {
        sout << "Empty Polynomial\n";
    }
    return sout;
}

istream& Polynom::extract(istream &sin)
{
    string input;
    cout << "Enter Polynomial -- ";
    
    getline(sin, input);
    
    vector <int> newContent;
    stringstream ss(input);
    
    int value;
    
    while (ss >> value)
    {
        newContent.push_back(value);
    }
    
    P.clear();
    for (int i : newContent)
    {
        P.push_back(i);
    }
    
    P.assign(newContent.begin(), newContent.end());
    
    return sin;
}

ostream& operator<<(ostream& Out, Polynom& RHS)
{
    RHS.insert(Out);
    return Out;
}

istream& operator>>(istream& In, Polynom& RHS)
{
    RHS.extract(In);
    return In;
}
