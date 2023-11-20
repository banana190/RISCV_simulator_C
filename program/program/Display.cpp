#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include "Decode.h"
#include "Display.h"

using namespace std;

void print(vector<Instruction> instructions) {
    for (int i = 0; i < instructions.size(); i++) {
        cout << "------------------------------------------------------------" << endl;
        cout << "original_ins:      " << instructions[i].original_ins << endl;
        cout << "type:              " << instructions[i].type << endl;
        cout << "instruction_name:  " << instructions[i].instruction_name << endl;
        cout << "opcode:            " << instructions[i].opcode << endl;
        cout << "func7:             " << instructions[i].func7 << endl;
        cout << "func3:             " << instructions[i].func3 << endl;
        cout << "rd:                " << instructions[i].rd << endl;
        cout << "rs1:               " << instructions[i].rs1 << endl;
        cout << "rs2:               " << instructions[i].rs2 << endl;
        cout << "imm1:              " << instructions[i].imm1 << endl;
        cout << "imm2:              " << instructions[i].imm2 << endl;
        cout << "jump:              " << instructions[i].jump << endl;
        cout << "binary_ins:        " << instructions[i].binary_ins << endl;
    }
}