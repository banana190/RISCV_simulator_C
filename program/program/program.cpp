#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdint>
#include "Decode.h"
#include "Fetch.h"
#include "Display.h"
#include "pipelining.h"
using namespace std;
// I use vector as register, from register[0]~register[31](32 registers) -Danny
vector<uint32_t> registers(32, 0);
// 2KB memory (2048 bytes) little endian
vector<uint8_t> memory(2048, 0);

vector<string> original_instruction;
vector<Instruction> pipelines;
vector<Instruction> decoded_instruction;

int instructionMode()
{
    for (int i = 0; i < decoded_instruction.size(); i++)
    {
        Instruction temp;
        temp = run_one_inst(decoded_instruction[i]);
        if (temp.instruction_name == "beq" && temp.ALUOutput == 1)
        {
            int j = std::bitset<32>(temp.imm).to_ulong();
            cout << "\nThis instruction is: " << temp.original_ins << "\nJump to the " << j + 1 << "th instruction\n";
            i = j - 1;
        }
        else if (temp.instruction_name != "mul")
        {
            int output = temp.ALUOutput;
            cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
        }
        else
        {
            long long int output = temp.mul_ALUOutput;
            cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
        }
        _getch();
    }
    return 0;
}

int cycleMode()
{
    // original_instruction and decoded_instruction are both empty.
    // I'll figure out the input format is "sample.g" or not tmrw.
    // update : we should make a txt file to store the instructions.
    unsigned int cycle;
    for (cycle = 0; cycle >= 0; cycle++)
    {
        pipelines = run_pipelining(decoded_instruction, pipelines);
        if (pipelines.size() >= 5)
        {
            int empty = 0;
            for (int i = 0; i < 5; i++)
            {
                // be sure that there is all empty instructions in vector.
                if (pipelines[i].kind == "17")
                    empty++;
            }
            if (empty == 5)
                break;
        }
        for (int k = 0; k < pipelines.size(); k++)
        {
            switch (k)
            {
            case 0:
                cout << "\033[0;33mIF stage:\033[0m\n";
                break;
            case 1:
                cout << "\033[0;33mID stage:\033[0m\n";
                break;
            case 2:
                cout << "\033[0;33mEx stage:\033[0m\n";
                break;
            case 3:
                cout << "\033[0;33mMem stage:\033[0m\n";
                break;
            case 4:
                cout << "\033[0;33mWb stage:\033[0m\n";
                break;
            }
            Instruction temp = pipelines[k];
            if (temp.instruction_name == "beq" && temp.ALUOutput == 1)
            {
                int j = std::bitset<32>(temp.imm).to_ulong();
                cout << "\nThis instruction is: " << temp.original_ins << "\nJump to the " << j + 1 << "th instruction\n";
                k = j - 1;
            }
            else if (temp.instruction_name != "mul")
            {
                int output = temp.ALUOutput;
                cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
            }
            else
            {
                long long int output = temp.mul_ALUOutput;
                cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
            }
        }
        cout << "-------------------------------------------\n";
        _getch();
    }
    pipelines.erase(pipelines.begin(), pipelines.end());
    cout << "Using " << cycle << " cycles" << endl;
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
        cout << "4 key instruction mode\n";
        cout << "5 print instruction\n";
        cout << "6 decode\n";
        cout << "7 lucky seven\n";
        cout << "8 read instruction.txt\n";

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
            original_instruction = fetch1();
            break;
        case 5:
            print(decoded_instruction);
            break;
        case 6:
            decoded_instruction = decode(original_instruction);
            // linking the instruction
            for (int i = 0; i < decoded_instruction.size() - 1; ++i)
            {
                decoded_instruction[i].nextInstruction = &decoded_instruction[i + 1];
            }
            decoded_instruction.back().nextInstruction = nullptr;
            break;
        case 7:
            decode(original_instruction);
            break;
        case 8:
            original_instruction = fetch_txt();
            decoded_instruction = decode(original_instruction);
            // linking the instruction
            for (int i = 0; i < decoded_instruction.size() - 1; ++i)
            {
                decoded_instruction[i].nextInstruction = &decoded_instruction[i + 1];
            }
            decoded_instruction.back().nextInstruction = nullptr;
            break;
        case 9:
            break;
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