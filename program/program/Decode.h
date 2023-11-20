#include <vector>
#include <String.h>

using namespace std;

vector<string> decode(vector<string> instruction);

vector<string> split(const string &s, char delim);

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
	string binary_ins = "";
	string jump = "";
};

vector<Instruction> decode(vector<string> instruction);

vector<string> split(const string &s, char delim);