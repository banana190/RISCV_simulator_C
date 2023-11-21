#include <iostream>
#include <vector>
#include <bitset>
#include "Decode.h"
using std::string;
using std::vector;
extern vector<uint8_t> memory;
extern vector<uint32_t> registers;

void Add_wb(Instruction adding)
{
    int rd = std::bitset<32>(adding.rd).to_ulong();
    registers[rd] = adding.ALUOutput;
}

void Sub_wb(Instruction subtracting)
{
    int rd = std::bitset<32>(subtracting.rd).to_ulong();
    registers[rd] = subtracting.ALUOutput;
}

void Addi_wb(Instruction addiing)
{
    int rd = std::bitset<32>(addiing.rd).to_ulong();
    registers[rd] = addiing.ALUOutput;
}

void Mul_wb(Instruction multipling)
{
    int rd = std::bitset<32>(multipling.rd).to_ulong();
    std::bitset<64> temp(multipling.mul_ALUOutput);
    std::bitset<32> first32Bits;
    std::bitset<32> last32Bits;

    for (int i = 0; i < 32; i++)
    {
        first32Bits[i] = temp[i];
        last32Bits[i] = temp[i + 32];
    }
    registers[rd] = first32Bits.to_ulong();
    registers[rd + 1] = last32Bits.to_ulong();
}

void Lui_wb(Instruction loading_upper)
{
    int rd = std::bitset<32>(loading_upper.rd).to_ulong();
    registers[rd] = loading_upper.ALUOutput;
}

void And_wb(Instruction anding)
{
    int rd = std::bitset<32>(anding.rd).to_ulong();
    registers[rd] = anding.ALUOutput;
}

void Andi_wb(Instruction andiing)
{
    int rd = std::bitset<32>(andiing.rd).to_ulong();
    registers[rd] = andiing.ALUOutput;
}

void Or_wb(Instruction oring)
{
    int rd = std::bitset<32>(oring.rd).to_ulong();
    registers[rd] = oring.ALUOutput;
}
void Ori_wb(Instruction oriing)
{
    int rd = std::bitset<32>(oriing.rd).to_ulong();
    registers[rd] = oriing.ALUOutput;
}
void Sll_wb(Instruction Lshifting)
{
    int rd = std::bitset<32>(Lshifting.rd).to_ulong();
    registers[rd] = Lshifting.ALUOutput;
}

void Srl_wb(Instruction Rshifting)
{
    int rd = std::bitset<32>(Rshifting.rd).to_ulong();
    registers[rd] = Rshifting.ALUOutput;
}

void Slti_wb(Instruction less_than)
{
    int rd = std::bitset<32>(less_than.rd).to_ulong();
    registers[rd] = less_than.ALUOutput;
}

void Sltiu_wb(Instruction less_than)
{
    int rd = std::bitset<32>(less_than.rd).to_ulong();
    registers[rd] = less_than.ALUOutput;
}
// MEM part
void Lw_wb(Instruction loading)
{
    int rd = std::bitset<32>(loading.rd).to_ulong();
    for (int i = 0; i < 4; i++)
    {
        registers[rd] |= memory[loading.LMD + i] << (8 * i); // little endian 0A0B0C0D => memory[0] = 0D
    }
}

void Sw_wb(Instruction storing)
{
    // nothing to do here
}

void Beq_wb(Instruction branching)
{
    if (branching.ALUOutput == 1)
    {
        // WIP
        //  load the instruction in memory[now+offset]
    }
}
