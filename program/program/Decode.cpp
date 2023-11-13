#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include "Decode.h"

using namespace std;

// seperate string by a char
// example: 
// s-s-s seperate by  '-'    result in  ['s','s','s']
vector<string> split(const string& s, char delim) {
    vector<std::string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

vector<string> decode(vector<string> instruction) {
    vector<string> s;

  
    cout << "\n";
    return s;
}