#include <iostream>
#include <vector>
#include "32bit_inst_structure.h"
#include "Execution.h"
using std::string;
using std::vector;

// WIP
int main()
{
    // this instruction is the vector that decode.cpp generates.
    // fetching the binary inst : WIP
    vector<string> instructions;
    vector<inst *> inst_containers;

    if (!instructions.empty())
    {
        inst_containers.push_back(type_classifyer(instructions));
    }
}