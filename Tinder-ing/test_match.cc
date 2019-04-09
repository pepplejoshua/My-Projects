#include <iostream>
#include "member.h"
#include "match.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void showMenu();

int main() {
    match Match;
    
    ifstream file;
    string fileName = "./match.dat";
    file.open(fileName.c_str());
    
    while(!file.eof())
    {
        string input;
        string name;
        char gender;
        double ratings[5];
    
        getline(file, input);
        
        if (input.empty())
        {
            continue;
        }
        else
        {
            stringstream ss(input);
            
            ss >> name >> gender;
            int count = 5;
            for (int i = 0; i < count; ++i)
            {
                double num;
                ss >> num;
                ratings[i] = num;
            }
            
            Match.insert(name, gender, ratings);
        }
    }
    file.close();

    char loop = 'y';
    int choice = 0;
    
    showMenu();
    
    do
    {
        cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                string name;
                cout << "Enter member's name -- ";
                cin >> name;
                
                int index = Match.findMatch(name, 0);
                Match.doMatch(name, index, 0);
                cout << "Done\n";
                showMenu();
                break;
            }
            case 2:
            {
                char gender;
                string name;
                cout << "Enter name and gender [M] or [F] -- ";
                cin >> name >> gender;
                
                cout << "For each hobby, enter an overall rating (up to 1 decimal place)\n";
                cout << "Rating must be between 0 and 5.0\n";
                double enteredRatings[5] = {0,0,0,0,0};
                string hobbies[5] = {"Sex","Sleep","Movies","Horoscope", "Photography"};
                int count = 5;
                // get hobby ratings for the user
                for (int i = 0; i < count; ++i)
                {
                    double rating = 0;
                    cout << hobbies[i] << ": ";
                    cin >> rating;
        
                    if (rating < 0.0 || rating > 5.0)
                    {
                        cout << "Invalid rating\n";
                        --i;
                        continue;
                    }
                    else
                    {
                        enteredRatings[i] = rating;
                    }
                }
                Match.insert(name, gender, enteredRatings);
                showMenu();
                break;
            }
            case 3:
            {
                string name;
                cout << "Enter name of member to delete -- ";
                cin >> name;
                Match.deleteMember(name);
                showMenu();
                break;
            }
            case 4:
            {
                Match.showMembers();
                showMenu();
                break;
            }
            case 5:
            {
                Match.printLists(Match);
                showMenu();
                break;
            }
            case 0:
            {
                return 0;
                break;
            }
            default:
                break;
        }

    }
    while (loop == 'y');
    
    return 0;
}

void showMenu()
{
    cout << "\nMatching App\n";
    cout << "============\n";
    
    cout << "[1] Find match for a member\n";
    cout << "[2] Add member\n";
    cout << "[3] Delete member\n";
    cout << "[4] Print all members\n";
    cout << "[5] Print all members and their information\n";
    cout << "[0] Exit\n";
}
