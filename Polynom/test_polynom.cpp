//
//  main.cpp
//  Polynom
//
//  Created by Joshua Pepple on 2018-10-13.
//  Copyright © 2018 SlingShot. All rights reserved.
//

#include <iostream>
#include "Polynom.h"
#include <sstream>
#include <vector>

int main() {
    //Empty Polynomial
    Polynom A;
    // change contents of Polynom A
    cout << A;
    cin >> A;
    cout << "After input: " << A << endl << endl;
    
    int array[6] = {4, 0, -1, 2, 0, 0};
    vector<int> store;
    for(int i = 0; i < 6; ++i)
    {
        store.push_back(array[i]);
    }

    //Vector initialized
    Polynom B(store);

    cout << "Before setting: " << B << endl; // value is [4 0 -1 2 0 0]

    //Testing setCoeff at a degree
    B.setCoeff(0, 2);
    cout << "After setting: " << B << endl; // value will change to [4 0 -1 2 0 2]

    int value = 0;
    //Testing getCoefficient at a degree
    B.getCoeff(5, value);
    cout << "Coefficient at degree 5: " << value << endl; // This should print a '4'

    //Tesing Addition
    int arr1[4] = {3, 2, 1, 16};
    int arr2[3] = {1, 5, 6};

    store.clear();
    for(int i = 0; i < 4; ++i)
    {
        store.push_back(arr1[i]);
    }
    Polynom p(store);

    store.clear();
    for(int i = 0; i < 3; ++i)
    {
        store.push_back(arr2[i]);
    }
    Polynom q(store);

    Polynom result = p + q;
    //result should be [3 3 6 22]
    cout << "\nAddition\n" << p << " + " << q << " = " << result << endl;


    // Testing Subtraction
    Polynom resSub = p - q;

    cout << endl << "Subtraction\n" << p << " - " << q << " = " << resSub << endl;

    //testing double operator(double x)
    int arr5[4] = {7, 0, -1, 0};
    
    store.clear();
    for(int i = 0; i < 4; ++i)
    {
        store.push_back(arr5[i]);
    }

    Polynom Eval(store);
    
    // should print 54
    cout << "\nFor x = 2, " << Eval << " = " << Eval(2) << endl;
    
    return 0;
}
