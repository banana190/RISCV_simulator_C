#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <string>
#include <conio.h>
#include "Decode.h"
#include "Display.h"
#include <cstdint>
extern vector<uint8_t> memory;
extern vector<uint32_t> registers;
using namespace std;

void print(vector<Instruction> instructions)
{
    for (int i = 0; i < instructions.size(); i++)
    {
        cout << "------------------------------------------------------------" << endl;
        cout << "original_ins:      " << instructions[i].original_ins << endl;
        cout << "type:              " << instructions[i].type << endl;
        cout << "instruction_name:  " << instructions[i].instruction_name << endl;
        cout << "opcode:            " << instructions[i].opcode << endl;
        cout << "func7:             " << instructions[i].func7 << endl;
        cout << "func3:             " << instructions[i].func3 << endl;
        cout << "rd:                " << instructions[i].rd << endl;
        cout << "rs1:               " << instructions[i].rs1 << endl;
        cout << "rs2:               " << instructions[i].rs2 << endl;
        cout << "imm1:              " << instructions[i].imm1 << endl;
        cout << "imm2:              " << instructions[i].imm2 << endl;
        cout << "jump:              " << instructions[i].jump << endl;
        cout << "binary_ins:        " << instructions[i].binary_ins << endl;
    }
}

void pipeline_print(vector<Instruction> pipelines)
{
    for (int k = 0; k < pipelines.size() && k <= 4; k++)
    {
        switch (k)
        {
        case 0:
            cout << "\033[0;33m\nIF stage:\033[0m\n";
            break;
        case 1:
            cout << "\033[0;33m\nID stage:\033[0m\n";
            break;
        case 2:
            cout << "\033[0;33m\nEx stage:\033[0m\n";
            break;
        case 3:
            cout << "\033[0;33m\nMem stage:\033[0m\n";
            break;
        case 4:
            cout << "\033[0;33m\nWb stage:\033[0m\n";
            break;
        }
        Instruction temp = pipelines[k];
        if (temp.instruction_name == "beq")
        {
            if (temp.ALUOutput == 1)
            {
                int j = bitset<32>(temp.imm).to_ulong();
                cout << "\n\033[0;33mThis instruction is: " << temp.original_ins << "\nJump to the " << j + 1 << "th instruction\033[0m\n";
            }
            else
            {
                cout << "\nThis instruction is: " << temp.original_ins << endl;
            }
        }
        else if (temp.instruction_name == "mul" && k >= 2)
        {
            long long int output = temp.mul_ALUOutput;
            cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
        }
        else if (temp.instruction_name == "lw" && k >= 4)
        {
            int rd = bitset<32>(temp.rd).to_ulong();
            cout << "\nThis instruction is: " << temp.original_ins << "\nthe value load into register x" << rd << " is :" << registers[rd] << endl;
        }
        else if (temp.instruction_name == "sw" && k >= 3)
        {
            int output = temp.ALUOutput;
            int rs1 = bitset<32>(temp.rs1).to_ulong();
            cout << "\nThis instruction is: " << temp.original_ins << "\nthe value store into memory [" << output << ":" << output + 3 << "] is: " << registers[rs1] << endl;
        }
        else if (k == 2 && temp.kind != "17")
        {
            int output = temp.ALUOutput;
            cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
        }
        else if (k == 4 && temp.kind != "17")
        {
            int output = temp.ALUOutput;
            int rd = bitset<32>(temp.rd).to_ulong();
            cout << "\nThis instruction is: " << temp.original_ins << "\nthe value load into register x" << rd << " is :" << output << endl;
        }
        else if (k <= 4)
        {
            cout << "\nThis instruction is: " << temp.original_ins << endl;
        }
    }
    cout << "-------------------------------------------\n";
    _getch();
}
int instruction_mode_print(Instruction temp, int i)
{
    if (temp.instruction_name == "beq" && temp.ALUOutput == 1)
    {
        int j = std::bitset<32>(temp.imm).to_ulong();
        cout << "\nThis instruction is: " << temp.original_ins << "\nJump to the " << j + 1 << "th instruction\n";
        i = j - 1;
    }
    else if (temp.instruction_name == "mul")
    {
        long long int output = temp.mul_ALUOutput;
        cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
    }
    else if (temp.instruction_name == "lw")
    {
        int output = temp.LMD;
        int rd = std::bitset<32>(temp.rd).to_ulong();
        cout << "\nThis instruction is: " << temp.original_ins << "\nthe value load into register x" << rd << " is :" << output << endl;
    }
    else if (temp.instruction_name == "sw")
    {
        int output = temp.ALUOutput;
        int rs1 = std::bitset<32>(temp.rs1).to_ulong();
        cout << "\nThis instruction is: " << temp.original_ins << "\nthe value store into memory [" << output << ":" << output + 3 << "] is: " << registers[rs1] << endl;
    }
    else
    {
        int output = temp.ALUOutput;
        cout << "\nThis instruction is: " << temp.original_ins << "\nthe ALUoutput is : " << output << endl;
    }
    _getch();
    return i;
}
