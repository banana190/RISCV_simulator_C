#include <vector>
#include <String.h>

using namespace std;

class Instruction
{
public:
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
	string imm = "";
	int ALUOutput = 0;
	long long int mul_ALUOutput = 0;
	int LMD = 0;
	int kind = 0;
};

vector<Instruction> decode(vector<string> instruction);

vector<string> split(const string &s, char delim);