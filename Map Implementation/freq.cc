#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include "Map.h"
#include <iomanip>

using namespace std;

// Pair used for final sorting with vector
struct Pair {
    string word;
    int freq;
};

//functions
vector<string> parse(ifstream&);
string to_lowcase(const string);
Map<string, int> word_frequencies(vector<string>);
void display(Map<string, int>);


int main() {
    // variables
    ifstream input;
    vector <string> entries;
    
    //get input from file and take a strings to lowercase
    entries = parse(input);
    
    transform(entries.begin(), entries.end(), entries.begin(), to_lowcase);
    
    //this calculates the frequency of words in entries
    Map<string, int> map = word_frequencies(entries);
    
    //this displays the words and their frequency in required format
    display(map);
    
    return 0;
}

// this reads in a file input and takes in strings and pushes them onto a vector of strings
// It returns the vector of strings, parsed
vector<string> parse(ifstream& input)
{
    vector<string> parsed;
    
    //change this file name to your input file name
    input.open("./words.data");
    
    while(!input.eof())
    {
        string word;
        input >> word;
        
        if (!word.empty())
        {
            parsed.push_back(word);
        }
    }
    return parsed;
}

// this takes a words and changes it to lower case. used with transform function for vector of strings.
// It returns a string, new_word
string to_lowcase(const string word)
{
    string new_word = "";

    for (char chr : word)
        new_word += tolower(chr);

    return new_word;
}

// this function takes a vector of words (strings) and computes the frequency of each words
// It keeps the result in a vector of Pairs (word, freq) which is in turn used to feed our Map object.
// The Map object handles sorting the entries based on words which can then be accessed using their index
Map<string, int> word_frequencies(vector<string> words)
{
    vector<Pair> counted;
    Map<string, int> new_words;
    
    for (string i : words)
    {
        if (!(i.empty()))
        {
            bool found = false;
            for(Pair j : counted)
            {
                if (j.word.compare(i) == 0)
                {
                    found = true;
                    break;
                    
                }
            }
            
            if(!found)
            {
                Pair item;
                item.word = i;
                item.freq = 1;
                counted.push_back(item);
            }
            else
            {
                for(int j = 0; j < counted.size(); ++j)
                {
                    if (counted[j].word.compare(i) == 0)
                    {
                        string w = counted[j].word;
                        int f = counted[j].freq;
                        
                        counted.erase(counted.begin()+j);
                        f++;
                        Pair temp;
                        temp.word = w;
                        temp.freq = f;
                        counted.push_back(temp);
                        break;
                    }
                }
            }
        }
    }
    
    for (Pair i : counted)
    {
        new_words.insert(i.word, i.freq);
    }
  
    return new_words;
}

//this displays the formatted results
void display(Map<string, int> freq_map)
{
    cout << "Word" << setw(31) << "Frequency\n";
    cout << "--------------------" << setw(14) << "---------" << endl;
    for (int i = 0; i < freq_map.size(); ++i)
    {
        string key = freq_map.index(i);
        int value = freq_map.find(key);
        cout << left << setw(20) << key << right << setw(14)<< value << endl;
    }
}
