#include "member.h"
#include <string>
#include <iostream>

using namespace std;

member::member()
{
    maxNumberOfRatings = 5;
}
member::member(string name, char gender)
{
    maxNumberOfRatings = 5;
    memberName = name;
    numberOfHobbies = 0;
    this->gender = gender;
    status = -1;
}

int member::getMaxNumberOfRatings() const
{
    return maxNumberOfRatings;
}

vector< double > member::getHobbiesRatings() const
{
    return hobbiesRatings;
}

int member::getStatus() const
{
    return status;
}

void member::setStatus(const int newStatus)
{
    status = newStatus;
}

int member::getNumberOfHobbies() const
{
    return numberOfHobbies;
}

string member::getName() const
{
    return memberName;
}

void member::changeRatings(const double newRatings[])
{
    hobbiesRatings.clear();
    int arraySize = 5;
    numberOfHobbies = 0;
    for(int i = 0; i < arraySize; ++i)
    {
        if (newRatings[i] == 0)
        {
            hobbiesRatings.push_back(0);
        }
        else
        {
            hobbiesRatings.push_back(newRatings[i]);
            numberOfHobbies++;
        }
    }
}
