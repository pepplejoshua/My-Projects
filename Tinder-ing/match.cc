#include "match.h"
#include <iostream>
#include <vector>
#include <string>
#include "member.h"
#include <cmath>

using namespace std;

// constructor
match::match()
{
    hobbies.push_back("Sex");
    hobbies.push_back("Sleep");
    hobbies.push_back("Movies");
    hobbies.push_back("Horoscope");
    hobbies.push_back("Photography");
}

int match::searchList(const string name, const char gender) const
{
    if (gender == 'M')
    {
        for (int i = 0; i < maleMembers.size(); ++i)
        {
            int found = maleMembers[i].getName().compare(name);
            
            if (found == 0)
            {
                return i;
            }
            else
                continue;
        }
    }
    else if (gender == 'F')
    {
        for (int i = 0; i < femaleMembers.size(); ++i)
        {
            int found = femaleMembers[i].getName().compare(name);
            
            if (found == 0)
            {
                return i;
            }
            else
                continue;
        }
    }
    // cout << "Name(" << name << ") doesn't exist" << endl;
    return -1;
}

// used to add members during testing
int match::insert(const string name, const char gender, const double enteredRatings[])
{
    int searchResult = searchList(name, gender);
    if (searchResult == -1)
    {
        member newMember(name, gender);
        
        newMember.changeRatings(enteredRatings);
        
        if (gender == 'M')
        {
            maleMembers.push_back(newMember);
            return (int) maleMembers.size()-1;
        }
        else if (gender == 'F')
        {
            femaleMembers.push_back(newMember);
            return (int) femaleMembers.size()-1;
        }
        
    }
    cout << "Name(" << name <<") already exists" << endl;
    return searchResult;
}

void match::showMembers() const
{
    cout << "==================" << endl;
    cout << "== Male members ==" << endl;
    for (int i = 0; i < maleMembers.size(); ++i)
    {
        member current = maleMembers[i];
        cout << current.getName();
        
        if (current.getStatus() == -1)
        {
            cout << ": Single\n";
        }
        else
        {
            cout << ": Matched\n";
        }
    }
    
    cout << "\n=====================" << endl;
    cout << "=== Female members ==" << endl;
    for (int i = 0; i < femaleMembers.size(); ++i)
    {
        member current = femaleMembers[i];
        cout << current.getName();
        
        if (current.getStatus() == -1)
        {
            cout << ": Single\n";
        }
        else
        {
            cout << ": Matched\n";
        }
    }
}

double match::computeScores(const string memberA, const string memberB)
{
    int searchResultA = searchList(memberA, 'M');
    int searchResultB = searchList(memberB, 'F');
    
    if (searchResultA != -1 && searchResultB != -1)
    {
        double pqProductSum = 0;
        double pSum = 0;
        double qSum = 0;
        vector < double > p = maleMembers[searchResultA].getHobbiesRatings();
        vector < double > q = femaleMembers[searchResultB].getHobbiesRatings();
        
        for (int i = 0; i < p.size(); ++i)
        {
            pqProductSum += p[i] * q[i];
            pSum += pow(p[i], 2);
            qSum += pow(q[i], 2);
            
        }
        pSum = sqrt(pSum);
        qSum = sqrt(qSum);
        
        double denominator = pSum * qSum;
        double cosineSimilarity = pqProductSum / denominator;
        return cosineSimilarity;
    }
    return -1;
    
}

int match::findMatch(const string mname, const double score)
{
    char gend = searchList(mname, 'M') == -1 ? 'F' : 'M';
    
    double maxScore = score;
    
    if (gend == 'M')
    {
        int count = 0;
        for (int i = 0; i < femaleMembers.size(); ++i)
        {
            double calculatedScore = computeScores(mname, femaleMembers[i].getName());
            if ((calculatedScore >= maxScore) && femaleMembers[i].getStatus() == -1)
                 count = i;
        }
        return count;
    }
    else if (gend == 'F')
    {
        int count = 0;
        for (int i = 0; i < maleMembers.size(); ++i)
        {
            double calculatedScore = computeScores(maleMembers[i].getName(), mname);
            if ((calculatedScore >= maxScore) && maleMembers[i].getStatus() == -1)
                count = i;
        }
        return count;
    }
    return -1;
}

bool match::doMatch(const string name, const int index, const double score)
{
    int potentialMatch = findMatch(name, score);
    
    if (potentialMatch == index)
    {
        int maleIndex = searchList(name, 'M');
        int femaleIndex = searchList(name, 'F');
        
        if (maleIndex != -1)
        {
            if (maleMembers[maleIndex].getStatus() == -1)
            {
                maleMembers[maleIndex].setStatus(potentialMatch);
                femaleMembers[index].setStatus(maleIndex);
                return true;
            }
            
        }
        else if (femaleIndex != -1)
        {
            if (femaleMembers[femaleIndex].getStatus() == -1)
            {
                femaleMembers[femaleIndex].setStatus(potentialMatch);
                maleMembers[index].setStatus(femaleIndex);
                return true;
            }
        }
    }
    return false;
}

void match::updateStatus(const string name)
{
    int index = searchList(name, 'M');
    
    if (index == -1)
    {
        index = searchList(name, 'F');
        if (index == -1)
            return;
        int partnerIndex = femaleMembers[index].getStatus();
        femaleMembers[index].setStatus(-1);
        maleMembers[partnerIndex].setStatus(-1);
    }
    else if (index != -1)
    {
        int partnerIndex = maleMembers[index].getStatus();
        maleMembers[index].setStatus(-1);
        femaleMembers[partnerIndex].setStatus(-1);
    }
}

void match::deleteMember(const string name)
{
    updateStatus(name);
    
    int index = searchList(name, 'M');
    
    if (index == -1)
    {
        index = searchList(name, 'F');
        if (index == -1)
            return;
        femaleMembers.erase(femaleMembers.begin()+index);
    }
    else if (index != -1)
    {
        maleMembers.erase(maleMembers.begin()+index);
    }
}

void match::printLists(match Match) const
{
    cout << "Male members: \n";
    int mCount = 0;
    for (int i = 0; i < Match.getMaleMembers().size(); ++i)
    {
        member male = Match.getMaleMembers().at(i);
        cout << ++mCount << ". " << male.getName() << endl;
        
        if (male.getStatus() == -1)
        {
            cout << "Single\n";
        }
        else
        {
            int index = male.getStatus();
            cout << "Matched with " << Match.getFemaleMembers().at(index).getName() << endl;
        }
        
        cout << "Hobbies and Ratings: \n";
        for (int i = 0; i < male.getHobbiesRatings().size(); ++i)
        {
            cout << hobbies[i] << ": " << male.getHobbiesRatings()[i] << endl;
        }
        cout << endl;
    }
    
    
    cout << "Female members: \n" << endl;
    int fCount = 0;
    for (int i = 0; i < Match.femaleMembers.size(); ++i)
    {
        member female = Match.femaleMembers[i];
        cout << ++fCount << ". " << female.getName() << endl;
        
        if (female.getStatus() == -1)
        {
            cout << "Single\n";
        }
        else
        {
            int index = female.getStatus();
            cout << "Matched with " << Match.getMaleMembers().at(index).getName() << endl;
        }
        
        cout << "Hobbies and Ratings: \n";
        for (int i = 0; i < female.getHobbiesRatings().size(); ++i)
        {
            cout << hobbies[i] << ": " << female.getHobbiesRatings()[i] << endl;
        }
        cout << endl;
    }
}
vector < member > match::getFemaleMembers() const
{
    return this->femaleMembers;
}

vector < member > match::getMaleMembers() const
{
    return this->maleMembers;
}
