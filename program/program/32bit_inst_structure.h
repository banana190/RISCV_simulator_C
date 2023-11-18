#include <iostream>
#include <vector>
using std::string;
using std::vector;

class R_inst // add sub mul and or sll srl
{
private:
    R_inst *next_instruction;

public:
    string func_7;
    string rs2;
    string rs1;
    string func_3;
    string rd;
    string opcode;
};

class I_inst // addi lw andi ori slti sltiu
{
private:
    I_inst *next_instruction;

public:
    string imm;
    string rs1;
    string func3;
    string rd;
    string opcode;
};

class S_inst // sw
{
private:
    S_inst *next_instruction;

public:
    string imm11_5;
    string rs2;
    string rs1;
    string imm4_0;
    string opcode;
};

class B_inst // beq
{
private:
    B_inst *next_instruction;

public:
    string imm12;
    string imm10_5;
    string rs2;
    string rs1;
    string func3;
    string imm4_1;
    string imm11;
    string opcode;
};

class U_inst // lui
{
private:
    U_inst *next_instruction;

public:
    string imm;
    string rd;
    string opcode;
};
