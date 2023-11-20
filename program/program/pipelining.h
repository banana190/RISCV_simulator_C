#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include "Decode.h"
using std::queue;
using std::string;
using std::vector;
extern vector<uint8_t> memory;
extern vector<uint32_t> registers;

void run_pipelining(vector<Instruction> instructions)
{
    queue<Instruction> q;
    for (int i = 0; i < instructions.size(); i++)
    {
    }
}