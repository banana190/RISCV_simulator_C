#include <iostream>
#include <vector>
#include <conio.h>
#include "Decode.h"
#include "Fetch.h"
#include "Display.h"

using namespace std;
// I use vector as register, from register[0]~register[31](32 registers) -Danny
vector<int> register;

vector<string> originalInstruction;

vector<Instruction> decoded_instruction;

int instructionMode()
{
    return 0;
}

int cycleMode()
{
    return 0;
}

int main()
{
    cout << "Welcome to  Wang and Chen's Simulation Program!\n";

    int mode;
    bool flag = true;

    vector<string> s;

    // allow user to choose mode or to quit
    while (flag)
    {
        fflush(stdin);
        cout << "\n------------------------------------------------------------------------------------------------\n";
        cout << "What kind of mode you want to select\n";
        cout << "1 Instruction mode\n";
        cout << "2 Cycle mode\n";
        cout << "3 exit\n";

        cin >> mode;
        switch (mode)
        {
        // actual function
        case 1:
            instructionMode();
            cout << "press anything to continue\n";
            _getch();
            break;
        case 2:
            cycleMode();
            cout << "press anything to continue\n";
            _getch();
            break;
        case 3:
            flag = false;
            break;


        // for test
        case 4:
            originalInstruction = fetch1();
            break;
        case 5:
            print(decoded_instruction);
            break;
        case 6:
            decoded_instruction = decode(originalInstruction);
            break;
        case 7:
            decode(originalInstruction);
            break;
        case 8: decoded_instruction = decode(originalInstruction); break;
        case 9: print(decoded_instruction); break;
        case 10: decode(originalInstruction); break;


        default:
            cout << "Wrong Number\n";
            flag = false;
            break;
        }
        fflush(stdin);
    }

    cout << "\nHave a good day!\n";
    return 0;
}