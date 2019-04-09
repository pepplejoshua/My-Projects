#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <cmath>
#include "./Ternary.h"

using namespace std;

int main()
{
  Ternary a("-11011");

  cout << a.getDecimalValue() << endl;
  return 0;
}


//done functions
/*
initializers
plus()
minus()
times()
getDecimalValue()
insert(cout)
extract(cin)
ternarytodecimal()
decimaltoternary()
*/
