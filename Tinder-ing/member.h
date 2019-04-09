//
//  member.hpp
//  Tinder
//
//  Created by Joshua Pepple on 2018-10-31.
//  Copyright © 2018 SlingShot. All rights reserved.
//

#ifndef member_h
#define member_h
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class member
{
public:
    member();
    member(const string, const char);
    
    // returns status of the member, single or index of matched partner
    int getStatus() const;
    
    // sets the status of member
    void setStatus(const int);
    
    // returns the name of member
    string getName() const;
    // returns the number of hobbies this member has
    int getNumberOfHobbies() const;
    
    // change hobbies' ratings
    void changeRatings(const double newRatings[]);
    
    // get hobbies' ratings
    vector< double > getHobbiesRatings() const;
    
protected:
    vector < double > hobbiesRatings;//ratings of listed hobbies
    
private:
    int getMaxNumberOfRatings() const;
    string memberName;//name of member
    int numberOfHobbies;//count of rated hobbies
 
    int maxNumberOfRatings;
    int status; //current status
    char gender; //gender
};
#endif /* member_h */
