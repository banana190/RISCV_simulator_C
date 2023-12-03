#include <iostream>
#include <vector>
#include <bitset>
#include "Decode.h"
using std::string;
using std::vector;
extern vector<uint8_t> memory;
extern vector<uint32_t> registers;

int Lw_mem(Instruction loading)
{
    int LMD;
    for (int i = 0; i < 4; i++)
    {
        LMD |= memory[loading.ALUOutput + i] << (8 * i); // little endian 0A0B0C0D => memory[0] = 0D
    }
    return LMD;
}

void Sw_mem(Instruction storing)
{
    int rs1 = std::bitset<32>(storing.rs1).to_ulong();
    memory[storing.ALUOutput + 3] = (registers[rs1] >> 24) & 0xFF;
    memory[storing.ALUOutput + 2] = (registers[rs1] >> 16) & 0xFF;
    memory[storing.ALUOutput + 1] = (registers[rs1] >> 8) & 0xFF;
    memory[storing.ALUOutput] = registers[rs1] & 0xFF;
}

int Beq_mem(Instruction branching)
{
    if (branching.ALUOutput == 1)
    {
        int LMD = std::bitset<32>(branching.imm).to_ulong();
        return LMD;
    }
    else
        return 0;
}
