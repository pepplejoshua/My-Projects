#ifndef TERNARY
#define TERNARY

#include <iostream>
#include <string>

using namespace std;

class Ternary
{
  public:
  Ternary();
  Ternary(const string init);
  Ternary plus(Ternary other);
  Ternary minus(Ternary other);
  Ternary times(Ternary other);
  int getDecimalValue() const;
  ostream& insert(ostream& os) const;
  istream& extract(istream& is);
  bool isTernary(const string entry);

  private:
  int decimal_equivalent;
  string ternary_equivalent;

  int solve(int value, int power) const;
  void ternarytodecimal(string str);
  string decimaltoternary(int decimal);


};

#endif
