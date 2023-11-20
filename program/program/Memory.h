#include <iostream>
#include <vector>
#include <bitset>
#include "Decode.h"
using std::string;
using std::vector;
extern vector<char> memory;
extern vector<int> registers;

int Lw(Instruction loading)
{
    int rd = std::bitset<32>(loading.rd).to_ulong();
    int rs1 = std::bitset<32>(loading.rs1).to_ulong();
    int LMD = loading.ALUOutput + registers[rs1];
    return LMD;
}

int Sw(Instruction storing)
{
    int rd = std::bitset<32>(storing.rd).to_ulong();
    int rs1 = std::bitset<32>(storing.rs1).to_ulong();
    int LMD = storing.ALUOutput + registers[rs1];
    return LMD;
}

int Beq(Instruction branching)
{
    if (branching.ALUOutput == 1)
    {
        int LMD = std::bitset<32>(branching.imm).to_ulong();
        return LMD;
    }
}
