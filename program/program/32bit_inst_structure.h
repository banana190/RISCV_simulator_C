#include <iostream>
#include <vector>
using std::string;
using std::vector;

class inst
{
};

class R_inst : public inst // add sub mul and or sll srl
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
    vector<string> execute();
    void ID_to_class(vector<string>);
};

class I_inst : public inst // addi lw andi ori slti sltiu
{
private:
    I_inst *next_instruction;

public:
    string imm;
    string rs1;
    string func3;
    string rd;
    string opcode;
    vector<string> execute();
};

class S_inst : public inst // sw
{
private:
    S_inst *next_instruction;

public:
    string imm11_5;
    string rs2;
    string rs1;
    string func3;
    string imm4_0;
    string opcode;
    vector<string> execute();
};

class SB_inst : public inst // beq
{
private:
    SB_inst *next_instruction;

public:
    string imm12;
    string imm10_5;
    string rs2;
    string rs1;
    string func3;
    string imm4_1;
    string imm11;
    string opcode;
    vector<string> execute();
};

class U_inst : public inst // lui
{
private:
    U_inst *next_instruction;

public:
    string imm;
    string rd;
    string opcode;
    vector<string> execute();
};
