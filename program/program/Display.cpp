#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include "Display.h"

using namespace std;

void print(vector<string> s) {
    cout << "\n-----print-----------------------------------------------\n";
    int size = s.size();
    for (int i = 0; i < size; i++) {
        cout << s[i] << " \n";
    }
    cout << "\n";
}