#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <map>
#include <string_view>
#include "Decode.h"

using namespace std;

const  map<string, vector<string>> instruction_template = {
    // R type
    // add x0,x0,x0
    //     type index opcode        func7   func3
    {"add",{"R", "0", "0110011", "0000000", "000"}},
    {"sub",{"R", "0", "0110011", "0100000", "000"}},
    {"sll",{"R", "0", "0110011", "0000000", "001"}},
    {"srl",{"R", "0", "0110011", "0000000", "101"}},
    {"and",{"R", "0", "0110011", "0000000", "111"}},
    {"or", {"R", "0", "0110011", "0000000", "110"}},
    {"mul",{"R", "0", "0110011", "0000001", "000"}},


    // I type
    {"lw",{"I","8"} },
    {"sw",{"I","9"} },
    {"andi",{"I","10"} },
    {"ori",{"I","11"} },
    {"addi",{"I","12"}},
    {"slti",{"I","13"} },
    {"sltiu",{"I","14"} },
    {"beq",{"I", "0", "0110011", "0000001", "000"}},
    // U type
    {"lui",{"U","15"} }
};

const  map<string, string> reg = {
    {"x0","00000"},
    {"x1","00001"},
    {"x2","00010"}
};


// seperate string by a char
// example: 
// s-s-s seperate by  '-'    result in  ['s','s','s']
vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}


string change_decimal_to_binary(string n) {
    int a = stoi(n);
    if (a == 0) {
        return "0";
    }

    string binary = "";

    // Convert decimal to binary
    while (a > 0) {
        // Prepend the remainder to the binary string
        binary = to_string(a % 2) + binary;
        a /= 2;
    }

    while (binary.size() < 5) {
        binary = "0" + binary;
    }

    return binary;
}



// For add,sub,sll,srl,and or mul
Instruction decode_r(vector<string> s) {
    Instruction ins;
    vector<string> result;
    
    ins.opcode = instruction_template.find(s[0])->second[2];
    ins.func7  = instruction_template.find(s[0])->second[3];
    ins.func3  = instruction_template.find(s[0])->second[4];;

    //x0,x0,x0 -> [x0, x0, x0]
    vector<string> split_result = split(s[1], ',');
    ins.rd  = reg.find(split_result[0])->second;
    ins.rs1 = reg.find(split_result[1])->second;
    if (split_result[2][0] != 'x') {
        ins.rs2 = change_decimal_to_binary(split_result[2]);
    }
    else {
        ins.rs2 = reg.find(split_result[2])->second;
    }

    ins.binary_ins = ins.func7 + ins.rs2 + ins.rs1 + ins.func3 + ins.rd + ins.opcode;

    return ins;
}

// For beq
Instruction decode_beq(vector<string> s) {
    Instruction ins;
    vector<string> result;

    ins.opcode = instruction_template.find(s[0])->second[2];
    ins.func7 = instruction_template.find(s[0])->second[3];
    ins.func3 = instruction_template.find(s[0])->second[4];;

    //x0,x0,x0 -> [x0, x0, x0]
    vector<string> split_result = split(s[1], ',');
    ins.rd = reg.find(split_result[0])->second;
    ins.rs1 = reg.find(split_result[1])->second;
    if (split_result[2][0] != 'x') {
        ins.rs2 = change_decimal_to_binary(split_result[2]);
    }
    else {
        ins.rs2 = reg.find(split_result[2])->second;
    }

    ins.binary_ins = ins.func7 + ins.rs2 + ins.rs1 + ins.func3 + ins.rd + ins.opcode;

    return ins;
}


vector<string> decode(vector<string> instruction) {
    try {
        vector<string> s;

        // store all the jump name and with to fill in address
        // example:
        // (0x0) bnq x0,x0,L1  -->jump    store index(0) and "L1"
        // when decode L1, get the L1'saddress and store in 0'address 
        map<string, int> jump;

        //store all instruction
       vector<Instruction> instructions;

        //store one instruction
        vector<string> split_result;


        for (int i = 0; i < instruction.size(); i++) {
            // seperate instruction and define each section of instruction
            //    check if is the jump instruction that previos instruction has use
            split_result = split(instruction[i], ':');
            if (split_result[0] != instruction[i]) {
                if (jump.find(split_result[0]) != jump.end()) {
                    int temp = jump.find(split_result[0])->second;

                    //TODO

                    instructions[temp].rd = change_decimal_to_binary(to_string(i));
                }
                split_result.erase(split_result.begin());
            }

            // example:
            // add x0,x0,x0 
            // split_result[0] =add  split_result[1]=x0,x0,x0
            split_result = split(split_result[0],' ');
            //second   ==>    {"R", "0", "0110011", "0000000","000"}
            //secondp[1] = 0, this is the index for switch
            int index = stoi(instruction_template.find(split_result[0])->second[1]);
            Instruction tempV;

            // translate into binary code
            switch (index) {
            case 0:
                //for R instruction
                tempV = decode_r(split_result);
                break;
            case 1: //for beq
                tempV = decode_beq(split_result);
                break;
            }
           
            
            tempV.original_ins = instruction[i];
            tempV.instruction_name = split_result[0];
            tempV.type = instruction_template.find(split_result[0])->second[0];

            //add jump
            if (!tempV.jump.empty()) {
                jump.insert({tempV.rd, i});
            }

            cout << tempV.original_ins << endl;
            cout << tempV.type << endl;
            cout << tempV.instruction_name << endl;
            cout << tempV.opcode << endl;
            cout << tempV.func7 << endl;
            cout << tempV.rd << endl;
            cout << tempV.rs1 << endl;
            cout << tempV.rs2 << endl;
            cout << tempV.binary_ins << endl;

            instructions.push_back(tempV);
        }

        return s;
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    };
}