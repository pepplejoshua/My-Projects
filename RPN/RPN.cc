#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//functions
void calculator();
int string_to_int(string);

int main() {
    
    // allows user perform multiple calculations
    while(true)
    {
        // main calculator function
        calculator();
        
        // handles user choice
        char choice = 'n';
        cout << "Use again? y - n: ";
        cin >> choice;
        
        if (choice == 'y')
            continue;
        else
            break;
    }
    
    return 0;
}

//main function of program to handle reading in entry
void calculator()
{
    vector<int> stck;
    string expression = "";
    
    cout << "Enter an expression -- ";
    
    //repeats loop until '.' is read
    while(true)
    {
        string entry;
        cin >> entry;
        expression += entry;
        expression += " ";
        
        //if the current entry is '.', stop reading in.
        if (!entry.compare("."))
            break;

        // if a '-' is read, it performs subtraction with the top 2
        // off the stack and stores the result of the calculation at the top of the stack
        else if (!entry.compare("-"))
        {
            if (stck.empty())
            {
                cout << "INVALID EXPRESSION\n";
                return;
            }
            else
            {
                // op1 and op2 store the operands respectively which are popped off the stack
                int op1, op2;
                op2 = stck.back();
                stck.pop_back();
                op1 = stck.back();
                stck.pop_back();
                // the calculation result is stored on the stack
                stck.push_back(op1 - op2);
            }
        }
        // if a '-' is read, it performs addition with the top 2
        // off the stack and stores the result of the calculation at the top of the stack
        else if (!entry.compare("+"))
        {
            if (stck.empty())
            {
                cout << "INVALID EXPRESSION\n";
                return;
            }
            else
            {
                // op1 and op2 store the operands respectively which are popped off the stack
                int op1, op2;
                op2 = stck.back();
                stck.pop_back();
                op1 = stck.back();
                stck.pop_back();
                // the calculation result is stored on the stack
                stck.push_back(op1 + op2);
            }
        }
        // if a '-' is read, it performs multiplication with the top 2
        // off the stack and stores the result of the calculation at the top of the stack
        else if (!entry.compare("*"))
        {
            if (stck.empty())
            {
                cout << "INVALID EXPRESSION\n";
                return;
            }
            else
            {
                // op1 and op2 store the operands respectively which are popped off the stack
                int op1, op2;
                op2 = stck.back();
                stck.pop_back();
                op1 = stck.back();
                stck.pop_back();
                // the calculation result is stored on the stack
                stck.push_back(op1 * op2);
            }
        }
        else
        {
            stck.push_back(string_to_int(entry));
        }
    }
    
    // an expression is invalid if after reading '.', there's more than 1 element on the stack
    if ((int) stck.size() > 1)
    {
        cout << "INVALID EXPRESSION\n";
        return;
    }
    else
        cout << "The result of '" << expression << "' is " << stck.at(0) << endl;
    
}

// this converts a string of number characters into an integer
int string_to_int(string entry)
{
    int value = 0;
    stringstream ss(entry);
    ss >> value;
    return value;
}
