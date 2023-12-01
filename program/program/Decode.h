#pragma once
#include <vector>
#include <String.h>

using namespace std;

class Instruction
{
public:
	Instruction *nextInstruction = nullptr;
	string original_ins = "";	  // add x0,x0,x0
	string type = "";			  // R
	string instruction_name = ""; // add
	string opcode = "";			  // 0010100
	string func7 = "";
	string func3 = "";
	string rd = "";
	string rs1 = "";
	string rs2 = "";
	string imm1 = "";
	string imm2 = "";
	string binary_ins = "";
	string jump = "";
	string imm = "";				 // the immediate
	int ALUOutput = 0;				 // the ALUOutput
	long long int mul_ALUOutput = 0; // this is the ALUOutput for multiplication
	int LMD = 0;					 // this is the data that load from mem to the register
	string kind = "";				 // this shows the instruction is e.g. add = 1 , sub = 2.
	int now = 0;					 // this shows the instruction is nth instruction.
};

vector<Instruction> decode(vector<string> instruction);

vector<string> split(const string &s, char delim);