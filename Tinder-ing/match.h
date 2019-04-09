#ifndef match_h
#define match_h
#include <stdio.h>
#include <vector>
#include "member.h"
using namespace std;

class match
{
public:
    match();
    
    // stores a new member
    int insert(const string name, const char gender, const double enteredRatings[]);
    
    // used to print members without details
    void showMembers() const;
    
    // searches specified list for name
    int searchList(const string name, const char gender) const;
    
    // computes score of similarity between 2 members
    double computeScores(const string memberA, const string memberB);
    
    // finds a match for the passed name
    int findMatch(const string mname, const double score);
    
    // tries to do a match and returns true if it finds a match
    bool doMatch(const string name, const int index, const double score);
    
    // updates relationship status to single
    void updateStatus(const string name);
    
    // deletes a member from list
    void deleteMember(const string name); // delete is a reserved word
    
    // prints the internal lists of a passed match type
    void printLists(match) const;

private:
    // returns vector for female members
    vector < member > getFemaleMembers() const;
    
    // returns vector for male members
    vector < member > getMaleMembers() const;
    
    // vector for storing hobbies
    vector < string > hobbies;
    
    // vector for male members
    vector < member > maleMembers;
    
    // vector for female members
    vector < member > femaleMembers;
};
#endif /* match_hpp */

