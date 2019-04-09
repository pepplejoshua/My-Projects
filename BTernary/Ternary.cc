#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <cmath>
#include "./Ternary.h"

using namespace std;

Ternary::Ternary()
{
  decimal_equivalent = 0;
  ternary_equivalent = "0";
}

Ternary::Ternary(const string init)
{
  ternarytodecimal(init);
  decimaltoternary(decimal_equivalent);
}

Ternary Ternary::plus(Ternary other)
{
  int sum = decimal_equivalent + other.getDecimalValue();

  return Ternary(decimaltoternary(sum));
}

Ternary Ternary::minus(Ternary other)
{
  int difference = decimal_equivalent - other.getDecimalValue();

  return Ternary(decimaltoternary(difference));
}


Ternary Ternary::times(Ternary other)
{
  int product = decimal_equivalent * other.getDecimalValue();

  return Ternary(decimaltoternary(product));
}

int Ternary::getDecimalValue() const
{
  return decimal_equivalent;
}


ostream& Ternary::insert(ostream& os) const
{
  os << ternary_equivalent << endl;
  return os;
}

istream& Ternary::extract(istream& is)
{
  string newEntry;
  is >> newEntry;

  ternarytodecimal(newEntry);
  decimaltoternary(decimal_equivalent);

  return is;
}


int Ternary::solve(int value, int power) const
{
  return value * pow(3, power);
}

void Ternary::ternarytodecimal(string str)
{
  vector<string> tokens;
  string temp;

  for(int i = 0; i < str.length(); i++)
  {
    if (str[i] == '-')
    {
      if (!temp.empty())
      {
        tokens.push_back(temp);
        temp = "";
        temp += str[i];
      }
      else
        temp += str[i];
    }
    else
    {
      temp += str[i];
      tokens.push_back(temp);
      temp = "";
    }
  }

  // use this to do the conversion from decimal to binary
  int maxPower = tokens.size() - 1;

  int sum = 0;

  for (int i = 0; i < tokens.size(); ++i)
  {
    int value;
    stringstream(tokens[i]) >> value;
    sum += solve(value, maxPower - i);
  }
  decimal_equivalent = sum;
}

string Ternary::decimaltoternary(int decimal)
{
  string s;
  int trit, temp;
  bool negative = false;

  temp = abs(decimal);

  if (decimal < 0)
    negative = true;

  while (temp > 0)
  {
    trit = temp % 3;
    if (trit == 0)
    {
      s = "0" + s;
      temp /= 3;
    }

    else if (trit == 1)
    {
      if(negative)
      {
        s = "-1" + s;
      }
      else
      {
        s = "1" + s;
      }
      temp /= 3;
    }

    else if (trit == 2)
    {
      if(negative)
      {
        s = "1" + s;
      }
      else
      {
        s = "-1" + s;
      }
      temp = (temp + 1) / 3;
    }
  }

  ternary_equivalent = s;
  return s;
}

bool Ternary::isTernary(const string entry)
{
  for(int i = 0; i < entry.length(); ++i)
  {
    if ((entry[i] != '-' && !isdigit(entry[i])) || (entry[i] !=  '1' || entry[i] != '0'))
    {
      return false;
    }
  }
  return true;
}
