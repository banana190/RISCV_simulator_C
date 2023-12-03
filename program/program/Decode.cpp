#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <map>
#include <string_view>
#include "Decode.h"

using namespace std;

const map<string, vector<string>> instruction_template = {
    // R type
    // add x0,x0,x0
    //     type index opcode        func7   func3   kind
    {"add", {"R", "0", "0110011", "0000000", "000", "1"}},
    {"sub", {"R", "0", "0110011", "0100000", "000", "2"}},
    {"sll", {"R", "0", "0110011", "0000000", "001", "13"}},
    {"srl", {"R", "0", "0110011", "0000000", "101", "14"}},
    {"and", {"R", "0", "0110011", "0000000", "111", "9"}},
    {"or", {"R", "0", "0110011", "0000000", "110", "11"}},
    {"mul", {"R", "0", "0110011", "0000001", "000", "4"}},

    // I type
    // nomal
    //       type index func3   opcode
    {"andi", {"I", "1", "111", "0010011", "10"}},
    {"ori", {"I", "1", "110", "0010011", "12"}},
    {"addi", {"I", "1", "000", "0010011", "3"}},
    {"slti", {"I", "1", "010", "0010011", "15"}},
    {"sltiu", {"I", "1", "011", "0010011", "16"}},
    // sw/lw
    //     type index func3   opcode
    {"lw", {"I", "2", "010", "0000011", "5"}},
    {"sw", {"I", "3", "010", "0100011", "6"}},
    // beq
    //      type index func3   opcode
    {"beq", {"I", "4", "000", "1100011", "7"}},
    // U type
    //      type index opcode
    {"lui", {"U", "5", "0110111", "8"}}};

const map<string, string> reg = {
    {"x0", "00000"},
    {"x1", "00001"},
    {"x2", "00010"},
    {"x3", "00011"},
    {"x4", "00100"},
    {"x5", "00101"},
    {"x6", "00110"},
    {"x7", "00111"},
    {"x8", "01000"},
    {"x9", "01001"},
    {"x10", "01010"},
    {"x11", "01011"},
    {"x12", "01100"},
    {"x13", "01101"},
    {"x14", "01110"},
    {"x15", "01111"},
    {"x16", "10000"},
    {"x17", "10001"},
    {"x18", "10010"},
    {"x19", "10011"},
    {"x20", "10100"},
    {"x21", "10101"},
    {"x22", "10110"},
    {"x23", "10111"},
    {"x24", "11000"},
    {"x25", "11001"},
    {"x26", "11010"},
    {"x27", "11011"},
    {"x28", "11100"},
    {"x29", "11101"},
    {"x30", "11110"},
    {"x31", "11111"},
};

// seperate string by a char
// example:
// s-s-s seperate by  '-'    result in  ['s','s','s']
vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

string change_decimal_to_binary(string n, int m)
{
    int a = stoi(n);
    string binary;
    if (a == 0)
    {
        string binary = "0";
    }
    else
    {
        binary = "";
    }

    // Convert decimal to binary
    while (a > 0)
    {
        // Prepend the remainder to the binary string
        binary = to_string(a % 2) + binary;
        a /= 2;
    }

    while (binary.size() < m)
    {
        binary = "0" + binary;
    }

    return binary;
}

// For add,sub,sll,srl,and or mul
Instruction decode_r(vector<string> s)
{
    Instruction ins;
    vector<string> result;

    ins.opcode = instruction_template.find(s[0])->second[2];
    ins.func7 = instruction_template.find(s[0])->second[3];
    ins.func3 = instruction_template.find(s[0])->second[4];
    ins.kind = instruction_template.find(s[0])->second[5];

    // x0,x0,x0 -> [x0, x0, x0]
    vector<string> split_result = split(s[1], ',');
    ins.rd = reg.find(split_result[0])->second;
    ins.rs1 = reg.find(split_result[1])->second;
    if (split_result[2][0] != 'x')
    {
        ins.rs2 = change_decimal_to_binary(split_result[2], 5);
    }
    else
    {
        ins.rs2 = reg.find(split_result[2])->second;
    }

    ins.binary_ins = ins.func7 + ins.rs2 + ins.rs1 + ins.func3 + ins.rd + ins.opcode;

    return ins;
}

// For i
Instruction decode_i(vector<string> s)
{
    Instruction ins;
    vector<string> result;

    ins.func3 = instruction_template.find(s[0])->second[2];
    ins.opcode = instruction_template.find(s[0])->second[3];
    ins.kind = instruction_template.find(s[0])->second[4];

    // x0,x1,1 -> [x0,x1,1]
    vector<string> split_result = split(s[1], ',');
    ins.rd = reg.find(split_result[0])->second;
    ins.rs1 = reg.find(split_result[1])->second;
    ins.imm = change_decimal_to_binary(split_result[2], 12);

    ins.binary_ins = ins.imm + ins.rs1 + ins.func3 + ins.rd + ins.opcode;

    return ins;
}

// For lw
Instruction decode_lw(vector<string> s)
{
    Instruction ins;
    vector<string> result;

    ins.func3 = instruction_template.find(s[0])->second[2];
    ins.opcode = instruction_template.find(s[0])->second[3];
    ins.kind = instruction_template.find(s[0])->second[4];

    vector<string> split_result = split(s[1], ',');
    ins.rd = reg.find(split_result[0])->second;

    // x0,24(x1) -> [x0, 24(x1)]
    vector<string> temp = split(split_result[1], '(');
    temp[1].pop_back();
    ins.rs1 = reg.find(temp[1])->second;
    ins.imm = change_decimal_to_binary(temp[0], 12);

    ins.binary_ins = ins.imm + ins.rs1 + ins.func3 + ins.rd + ins.opcode;

    return ins;
}

// For sw
Instruction decode_sw(vector<string> s)
{
    Instruction ins;
    vector<string> result;

    ins.func3 = instruction_template.find(s[0])->second[2];
    ins.opcode = instruction_template.find(s[0])->second[3];
    ins.kind = instruction_template.find(s[0])->second[4];

    vector<string> split_result = split(s[1], ',');
    ins.rs1 = reg.find(split_result[0])->second;
    // 24(x1) -> [24,x1)]
    vector<string> temp = split(split_result[1], '(');
    temp[1].pop_back();
    ins.rs2 = reg.find(temp[1])->second;
    ins.imm = change_decimal_to_binary(temp[0], 12);
    ins.imm1 = ins.imm.substr(0, 7);
    ins.imm2 = ins.imm.substr(7, 5);

    ins.binary_ins = ins.imm1 + ins.rs2 + ins.rs1 + ins.func3 + ins.imm2 + ins.opcode;

    return ins;
}

Instruction decode_beq(vector<string> s)
{
    Instruction ins;
    vector<string> result;

    ins.func3 = instruction_template.find(s[0])->second[2];
    ins.opcode = instruction_template.find(s[0])->second[3];
    ins.kind = instruction_template.find(s[0])->second[4];

    // x0,x0,L1 -> [x0, x0, 1]
    vector<string> split_result = split(s[1], ',');
    ins.rs1 = reg.find(split_result[0])->second;
    ins.rs2 = reg.find(split_result[1])->second;
    ins.jump = split_result[2];

    return ins;
}

Instruction decode_lui(vector<string> s)
{
    Instruction ins;
    vector<string> result;

    ins.opcode = instruction_template.find(s[0])->second[2];
    ins.kind = instruction_template.find(s[0])->second[3];

    // x0,231213 -> [x0, ]
    vector<string> split_result = split(s[1], ',');
    ins.rd = reg.find(split_result[0])->second;
    string temp = split_result[1];
    ins.imm = change_decimal_to_binary(temp, 20);

    ins.binary_ins = ins.imm + ins.rd + ins.opcode;

    return ins;
}

vector<Instruction> decode(vector<string> instruction)
{
    // store all instruction
    vector<Instruction> instructions;
    try
    {
        // store all the jump name and with to fill in address
        // example:
        // (0x0) bnq x0,x0,L1  -->jump    store index(0) and "L1"
        // when decode L1, get the L1'saddress and store in 0'address
        map<string, int> jump;

        // store one instruction
        vector<string> split_result;

        for (int i = 0; i < instruction.size(); i++)
        {
            // check if there is a jump instruction or not
            split_result = split(instruction[i], ':');
            if (split_result[0] != instruction[i])
            {
                if (jump.find(split_result[0]) != jump.end())
                {
                    int previous_instruction = jump.find(split_result[0])->second;
                    instructions[previous_instruction].imm = change_decimal_to_binary(to_string(i), 12);
                    instructions[previous_instruction].imm1 = instructions[previous_instruction].imm.substr(0, 7);
                    instructions[previous_instruction].imm2 = instructions[previous_instruction].imm.substr(7, 5);
                    instructions[previous_instruction].binary_ins = instructions[previous_instruction].imm1 + instructions[previous_instruction].rs2 + instructions[previous_instruction].rs1 + instructions[previous_instruction].func3 + instructions[previous_instruction].imm2 + instructions[previous_instruction].opcode;
                }
                split_result.erase(split_result.begin());
            }

            // example:
            // add x0,x0,x0
            // split_result[0] =add  split_result[1]=x0,x0,x0
            split_result = split(split_result[0], ' ');
            // second   ==>    {"R", "0", "0110011", "0000000","000"}
            // secondp[1] = 0, this is the index for switch
            int index = stoi(instruction_template.find(split_result[0])->second[1]);
            Instruction tempV;

            // translate into binary code
            switch (index)
            {
            case 0:
                // for R instruction
                tempV = decode_r(split_result);
                break;
            case 1: // for I instruction
                tempV = decode_i(split_result);
                break;
            case 2: // for lw
                tempV = decode_lw(split_result);
                break;
            case 3: // for sw
                tempV = decode_sw(split_result);
                break;
            case 4: // for beq
                tempV = decode_beq(split_result);
                break;
            case 5: // for lui
                tempV = decode_lui(split_result);
                break;
            }

            tempV.original_ins = instruction[i];
            tempV.instruction_name = split_result[0];
            tempV.type = instruction_template.find(split_result[0])->second[0];

            // add jump
            if (!tempV.jump.empty())
            {
                jump.insert({tempV.jump, i});
            }

            instructions.push_back(tempV);
        }

        return instructions;
    }
    catch (const exception &e)
    {
        cerr << "Exception caught: " << e.what() << endl;
        return instructions;
    };
}