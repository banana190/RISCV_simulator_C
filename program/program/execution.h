#include <iostream>
#include <vector>
#include "32bit_inst_structure.h"
using std::string;
using std::vector;

vector<int> ALU_control_input(vector<string> ALU_input)
{
}

// this build the class and return it.
inst *type_classifyer(vector<string> bin_inst)
{
    // type = "";
    inst *type = nullptr;
    if (!bin_inst.empty())
    {
        string opcode = bin_inst.back();
        if (opcode == "0110011") // type = "R";
        {
            temp = new R_inst();
            temp.func7 = bin_inst[0];
            temp.rs2 = bin_inst[1];
            temp.rs1 = bin_inst[2];
            temp.func3 = bin_inst[3];
            temp.rd = bin_inst[4];
            temp.opcode = bin_inst[5];
        }
        else if (opcode == "0010011" || opcode == "0000011") // type = "I";
        {
            temp = new I_inst();
            temp.imm = bin_inst[0];
            temp.rs1 = bin_inst[1];
            temp.func3 = bin_inst[2];
            temp.rd = bin_inst[3];
            temp.opcode = bin_inst[4];
        }
        else if (opcode == "0100011") // type = "S";
        {
            temp = new S_inst();
            temp.imm11_5 = bin_inst[0];
            temp.rs2 = bin_inst[1];
            temp.rs1 = bin_inst[2];
            temp.func3 = bin_inst[3];
            temp.imm4_0 = bin_inst[4];
            temp.opcode = bin_inst[5];
        }
        else if (opcode == "1100011") // type = "SB";
        {
            temp = new SB_inst();
            temp.imm12 = bin_inst[0];
            temp.imm10_5 = bin_inst[1];
            temp.rs2 = bin_inst[2];
            temp.rs1 = bin_inst[3];
            temp.func3 = bin_inst[4];
            temp.imm4_1 = bin_inst[5];
            temp.imm11 = bin_inst[6];
            temp.opcode = bin_inst[7];
        }
        else if (opcode == "0110111") // type = "U";
        {
            temp = new U_inst();
            temp.imm = bin_inst[0];
            temp.rd = bin_inst[1];
            temp.opcode = bin_inst[2];
        }
    }
    return temp;
}
