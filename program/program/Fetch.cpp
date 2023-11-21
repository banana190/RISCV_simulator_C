#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include "Fetch.h"

using namespace std;

vector<string> fetch1()
{
    cout << "\n------------------------------------------------------------------------------------------------\n";
    cout << "How many instructions do you want to enter?\n";
    cout << "number:";
    int num;
    string ins;
    cin >> num;
    // don't know why, first getline won't get any string
    getline(cin, ins);

    vector<string> s;

    for (int i = 1; i <= num; i++)
    {
        cout << "\nInstruction" << i << " :";
        getline(cin, ins);
        s.push_back(ins);
    }
    cout << "\n";
    return s;
}