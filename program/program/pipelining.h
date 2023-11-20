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

vector<Instruction> run_pipelining(vector<Instruction> instructions,vector<Instruction> pipelining,int cycle)
{
    pipelining.push_back(instructions[cycle]);
    for (int i = 0; i < 5; i++)
    {
        
    }
}