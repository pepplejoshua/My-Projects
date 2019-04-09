#include <iostream>
#include "Structured_Matrix.h"
#include "Symmetric_Matrix.h"
#include "Upper_Triangular_Matrix.h"
#include "Lower_Triangular_Matrix.h"

using namespace std;

// just to help with this file. Index struct to handle user input to Matrix access.
struct index
{
    int i;
    int j;
};

void process_str_matrix(Structured_Matrix *matrices[], int count, struct index in);
string reverse_string(string s, int l);
int seq_search(int a[], int key, int l);
int dt_rt(int n);

int main() {
    // Get the value of n
    int n = 0;
    cout << "What is the value of n [n x n] ? => ";
    cin >> n;
    
    // Used to store matrices
    Structured_Matrix *matrices[3];
    
    // Matrices
    Symmetric_Matrix mat(n);
    Upper_Triangular_Matrix mata(n);
    Lower_Triangular_Matrix matb(n);
    
    // keeping matrix types in storage
    matrices[0] = &mat;
    matrices[1] = &mata;
    matrices[2] = &matb;
    
    // values from array into Matrices
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            int in = 0;
            cout << "Enter => ";
            cin >> in;
            mat(i,j) = in;
            matb(i, j) = in;
        }
    }
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            mata(i, j) = mat(i, j);
        }
    }
    
    // Test index
    struct index in;
    cout << "Index: ";
    cin >> in.i >> in.j;
    
    process_str_matrix(matrices, 3, in);
    
    
    /* ******* PART 2 * *******/
    //reverse_string
    cout << "Enter string to reverse => ";
    string entry;
    cin >> entry;
    cout << entry << " reversed => " << reverse_string(entry, (int) entry.length()) << endl;
    
    //seq_search
    cout << "\nEnter number of entries to be searched -- ";
    int l;
    cin >> l;
    int a[l];
    for (int f = 0; f < l; ++f)
    {
        cout << "Enter -- ";
        cin >> a[f];
    }
    cout << "Enter key -- ";
    int key;
    cin >> key;
    
    cout << "key => " << key << " found at index " << seq_search(a, key, l) << endl;
    
    // dt_rt
    cout << "Eg: dt_rt(9832763) => " <<  dt_rt(9832763) << endl;
    cout << "Enter number -- ";
    int num;
    cin >> num;
    cout << "dt_rt(num) => " <<  dt_rt(num) << endl;
    return 0;
}

// This prints all Structured Matrices passed in.
void process_str_matrix(Structured_Matrix *matrices[], int count, struct index in)
{
    for (int i = 0; i < count; ++i)
    {
        Structured_Matrix *item = matrices[i];
        item->print();
        cout << endl;
        cout << "Largest row sum (absolute values): " << item->ifnform() << endl;
        cout << "Index [" << in.i << ", " << in.j << "] => " << item->operator()(in.i, in.j) << endl;
        cout << endl;
    }
}

string reverse_string(string s, int l)
{
    // this is the base case for recursion
    if (l == 0)
        return "";
    else
    {
        // this will store the string in reversed order over all recursive calls
        string reverse;
        // suppose s = "i am", reverse starts at => "m" + ("i a") which would become "ma" + ("i ") and so on
        // it takes the last character and appends to reverse
        reverse += s[l-1] + reverse_string(s, l-1);
        return reverse;
    }
}

int seq_search(int a[], int key, int l)
{
    //  this is the base case for recursion
    if (l == 0)
        return -1;
    else
    {
        // if the last element is the key, return the last index
        if (a[l-1] == key)
            return l-1;
        // else return the recursive solution
        else
            return seq_search(a, key, l-1);
    }
}

//that repeatedly sums the digits of the parameter n until the result is a single-digit number.
//For example, if the number in the parameter is 9832763, then the function repeatedly
//adds the digits as
//9 + 8 + 3 + 2 + 7 + 6 + 3 giving 38 which is a two-digit number so add the digits
//again: 8 + 3 giving 11 also a two-digit number so add the digits again: 1 + 1
//giving 2 which is a one-digit number. So the function returns the number 2.
int dt_rt(int n)
{
    //  this is the base case for recursion
    if (n == 0)
    {
        return 0;
    }
    else
    {
        // num stores the last digit of n
        int num = n % 10;
        // n then becomes n without the last digit stored in num
        n /= 10;
        // the sum to be calculated
        int sum = 0;
        // the sum is the sum of existing sum, num and the recursive addition solution of the changed n
        sum += num + dt_rt(n);
        // if at any point in the recursion, sum is a 2 digit number, we call the dt_rt() function on it
        // we need a single digit solution
        if (sum / 10 != 0)
        {
            sum = dt_rt(sum);
        }
        return sum;
    }
}

