#include <iostream>
#include <vector>
#include <bitset>
#include "32bit_inst_structure.h"
#include "Decode.h"
using std::string;
using std::vector;
extern vector<uint32_t> registers;
vector<int> ALU_control_input(vector<string> ALU_input)
{
}

// this build the class and return it.
// inst *type_classifyer(vector<string> bin_inst)
// {
//     // type = "";
//     inst *type = nullptr;
//     if (!bin_inst.empty())
//     {
//         string opcode = bin_inst.back();
//         if (opcode == "0110011") // type = "R";
//         {
//             R_inst temp = new R_inst();
//             temp.func_7 = bin_inst[0];
//             temp.rs2 = bin_inst[1];
//             temp.rs1 = bin_inst[2];
//             temp.func_3 = bin_inst[3];
//             temp.rd = bin_inst[4];
//             temp.opcode = bin_inst[5];
//         }
//         else if (opcode == "0010011" || opcode == "0000011") // type = "I";
//         {
//             inst temp = new I_inst();
//             temp.imm = bin_inst[0];
//             temp.rs1 = bin_inst[1];
//             temp.func3 = bin_inst[2];
//             temp.rd = bin_inst[3];
//             temp.opcode = bin_inst[4];
//         }
//         else if (opcode == "0100011") // type = "S";
//         {
//             temp = new S_inst();
//             temp.imm11_5 = bin_inst[0];
//             temp.rs2 = bin_inst[1];
//             temp.rs1 = bin_inst[2];
//             temp.func3 = bin_inst[3];
//             temp.imm4_0 = bin_inst[4];
//             temp.opcode = bin_inst[5];
//         }
//         else if (opcode == "1100011") // type = "SB";
//         {
//             temp = new SB_inst();
//             temp.imm12 = bin_inst[0];
//             temp.imm10_5 = bin_inst[1];
//             temp.rs2 = bin_inst[2];
//             temp.rs1 = bin_inst[3];
//             temp.func3 = bin_inst[4];
//             temp.imm4_1 = bin_inst[5];
//             temp.imm11 = bin_inst[6];
//             temp.opcode = bin_inst[7];
//         }
//         else if (opcode == "0110111") // type = "U";
//         {
//             temp = new U_inst();
//             temp.imm = bin_inst[0];
//             temp.rd = bin_inst[1];
//             temp.opcode = bin_inst[2];
//         }
//     }
//     return temp;
// }

int Add_ex(Instruction adding)
{
    int rd = std::bitset<32>(adding.rd).to_ulong();
    int rs1 = std::bitset<32>(adding.rs1).to_ulong();
    int rs2 = std::bitset<32>(adding.rs2).to_ulong();
    // registers[rd] = registers[rs1] + registers[rs2]; write back is not this part
    int ALUOutput = registers[rs1] + registers[rs2];
    return ALUOutput;
}

int Sub_ex(Instruction subtracting)
{
    int rd = std::bitset<32>(subtracting.rd).to_ulong();
    int rs1 = std::bitset<32>(subtracting.rs1).to_ulong();
    int rs2 = std::bitset<32>(subtracting.rs2).to_ulong();
    // registers[rd] = registers[rs1] - registers[rs2]; write back is not this part
    int ALUOutput = registers[rs1] - registers[rs2];
    return ALUOutput;
}

int Addi_ex(Instruction addiing)
{
    int rd = std::bitset<32>(addiing.rd).to_ulong();
    int rs1 = std::bitset<32>(addiing.rs1).to_ulong();
    int imm = std::bitset<32>(addiing.imm).to_ulong();
    // registers[rd] = registers[rs1] +imm; write back is not this part
    int ALUOutput = registers[rs1] + imm;
    return ALUOutput;
}

long long int Mul_ex(Instruction multipling)
{
    int rd = std::bitset<32>(multipling.rd).to_ulong();
    int rs1 = std::bitset<32>(multipling.rs1).to_ulong();
    int rs2 = std::bitset<32>(multipling.rs2).to_ulong();
    long long int ALUOutput = registers[rs1] * registers[rs2];
    return ALUOutput;
    // std::bitset<64> temp(result); write back is not this part
    // std::bitset<32> first32Bits;
    // std::bitset<32> last32Bits;

    // for (int i = 0; i < 32; i++)
    // {
    //     first32Bits[i] = temp[i];
    //     last32Bits[i] = temp[i + 32];
    // }
    // registers[rd] = first32Bits.to_ulong();
    // registers[rd + 1] = last32Bits.to_ulong();
}
// MEMORY part WIP
int Lw_ex(Instruction loading)
{
    int rd = std::bitset<32>(loading.rd).to_ulong();
    int rs1 = std::bitset<32>(loading.rs1).to_ulong();
    int imm = std::bitset<32>(loading.imm).to_ulong();
    int ALUOutput = registers[rs1] + imm;
    return ALUOutput;
}

int Sw_ex(Instruction storing)
{
    int rd = std::bitset<32>(storing.rd).to_ulong();
    int rs1 = std::bitset<32>(storing.rs1).to_ulong();
    int imm = std::bitset<32>(storing.imm).to_ulong();
    int ALUOutput = registers[rs1] + imm;
    return ALUOutput;
}
int Beq_ex(Instruction branching)
{
    int rd = std::bitset<32>(branching.rd).to_ulong();
    int rs1 = std::bitset<32>(branching.rs1).to_ulong();
    int rs2 = std::bitset<32>(branching.rs2).to_ulong();
    int ALUOutput = rs1 == rs2 ? 1 : 0;
    return ALUOutput;
}
//-----------------------------------------
int Lui_ex(Instruction loading_upper)
{
    int temp = std::bitset<32>(loading_upper.rd).to_ulong();
    std::bitset<32> imm(loading_upper.imm);
    std::bitset<32> rd = imm << 12; // shift 12 bit
    for (int i = 20; i < 32; i++)
    {
        rd[i] = 0; // clear 12 bit
    }
    // registers[temp] = rd.to_ulong(); WB
    int ALUOutput = rd.to_ulong();
    return ALUOutput;
}

int And_ex(Instruction anding)
{
    int temp_rd = std::bitset<32>(anding.rd).to_ulong();   // e.g. temp_rd = 5
    int temp_rs1 = std::bitset<32>(anding.rs1).to_ulong(); // temp_rs1 = 6
    int temp_rs2 = std::bitset<32>(anding.rs2).to_ulong(); // temp_rs2 = 7
    std::bitset<32> rs1(registers[temp_rs1]);              // rs1 = registers[6] = 80 to bin = 0101 0000
    std::bitset<32> rs2(registers[temp_rs2]);              // rs2 = registers[7] = 99 to bin = 0110 0011
    std::bitset<32> rd = rs1 & rs2;                        // rd = rs1 and rs2
    // registers[temp_rd] = rd.to_ulong(); WB
    int ALUOutput = rd.to_ulong();
    return ALUOutput;
}

int Andi_ex(Instruction andiing)
{
    int temp_rd = std::bitset<32>(andiing.rd).to_ulong();
    int temp_rs1 = std::bitset<32>(andiing.rs1).to_ulong();
    std::bitset<32> imm(andiing.imm);
    std::bitset<32> rs1(registers[temp_rs1]);
    std::bitset<32> rd = rs1 & imm;
    // registers[temp_rd] = rd.to_ulong();WB
    int ALUOutput = rd.to_ulong();
    return ALUOutput;
}

int Or_ex(Instruction oring)
{
    int temp_rd = std::bitset<32>(oring.rd).to_ulong();   // e.g. temp_rd = 5
    int temp_rs1 = std::bitset<32>(oring.rs1).to_ulong(); // temp_rs1 = 6
    int temp_rs2 = std::bitset<32>(oring.rs2).to_ulong(); // temp_rs2 = 7
    std::bitset<32> rs1(registers[temp_rs1]);             // rs1 = registers[6] = 80 to bin = 0101 0000
    std::bitset<32> rs2(registers[temp_rs2]);             // rs2 = registers[7] = 99 to bin = 0110 0011
    std::bitset<32> rd = rs1 | rs2;                       // rd = rs1 or rs2
    // registers[temp_rd] = rd.to_ulong(); WB
    int ALUOutput = rd.to_ulong();
    return ALUOutput;
}
int Ori_ex(Instruction oriing)
{
    int temp_rd = std::bitset<32>(oriing.rd).to_ulong();
    int temp_rs1 = std::bitset<32>(oriing.rs1).to_ulong();
    std::bitset<32> imm(oriing.imm);
    std::bitset<32> rs1(registers[temp_rs1]);
    std::bitset<32> rd = rs1 | imm;
    // registers[temp_rd] = rd.to_ulong(); WB
    int ALUOutput = rd.to_ulong();
    return ALUOutput;
}
int Sll_ex(Instruction Lshifting)
{
    int temp_rd = std::bitset<32>(Lshifting.rd).to_ulong();   // e.g. temp_rd = 5
    int temp_rs1 = std::bitset<32>(Lshifting.rs1).to_ulong(); // temp_rs1 = 6
    int temp_rs2 = std::bitset<32>(Lshifting.rs2).to_ulong(); // temp_rs2 = 7
    std::bitset<32> rs1(registers[temp_rs1]);                 // rs1 = registers[6] = 80 to bin = 0101 0000
    std::bitset<32> rd = rs1 << registers[temp_rs2];          // rd = rs1 << registers[7] = rs2
    // registers[temp_rd] = rd.to_ulong(); WB
    int ALUOutput = rd.to_ulong();
    return ALUOutput;
}

int Srl_ex(Instruction Rshifting)
{
    int temp_rd = std::bitset<32>(Rshifting.rd).to_ulong();
    int temp_rs1 = std::bitset<32>(Rshifting.rs1).to_ulong();
    int temp_rs2 = std::bitset<32>(Rshifting.rs2).to_ulong();
    std::bitset<32> rs1(registers[temp_rs1]);
    std::bitset<32> rd = rs1 >> registers[temp_rs2];
    // registers[temp_rd] = rd.to_ulong(); WB
    int ALUOutput = rd.to_ulong();
    return ALUOutput;
}

int Slti_ex(Instruction less_than)
{
    int rd = std::bitset<32>(less_than.rd).to_ulong();
    int rs1 = std::bitset<32>(less_than.rs1).to_ulong();
    int imm = std::bitset<32>(less_than.imm).to_ulong();
    // registers[rd] = registers[rs1] < imm ? 1 : 0; WB
    int ALUOutput = registers[rs1] < imm ? 1 : 0;
    return ALUOutput;
}

int Sltiu_ex(Instruction less_than)
{
    int rd = std::bitset<32>(less_than.rd).to_ulong();
    int rs1 = std::bitset<32>(less_than.rs1).to_ulong();
    unsigned int imm = std::bitset<32>(less_than.imm).to_ulong();
    // registers[rd] = registers[rs1] < imm ? 1 : 0;
    int ALUOutput = registers[rs1] < imm ? 1 : 0;
    return ALUOutput;
}
