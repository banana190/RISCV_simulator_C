#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <map>
#include <string_view>
#include "Decode.h"

using namespace std;

const  map<string, vector<string>> instructionTemplate = {
    // R type
    // add x0,x0,x0
    // type index(used for clasify) opcode func7
    {"add",{"R", "0", "0110011", "0000000"}},
    {"sub",{"R", "0", "0110011", "0100000"} },


    {"sll",{"R","0", "0110011", "0000000"} },
    {"srl",{"R","0", "0110011", "0000000"} },
    {"and",{"R","0", "0110011", "0000000"} },
    {"or",{"R","0", "0110011", "0000000"} },
    //mul x0,x0 
    {"mul",{"R","5"} },
    // beq x0,x0,L1
    {"beq",{"R","7"} },

    // I type
    {"lw",{"I","8"} },
    {"sw",{"I","9"} },
    {"andi",{"I","10"} },
    {"ori",{"I","11"} },
    {"addi",{"I","12"}},
    {"slti",{"I","13"} },
    {"sltiu",{"I","14"} },

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


// For add and sub
vector<string> decode1(vector<string> s) {
    vector<string> result;
    string opcode = instructionTemplate.find(s[0])->second[2];
    string func7  = instructionTemplate.find(s[0])->second[3];
    string func3 = "000";

    //x0,x0,x0 -> [x0, x0, x0]
    vector<string> split_result = split(s[1], ',');
    string rd = reg.find(split_result[0])->second;
    string rs1 = reg.find(split_result[1])->second;
    string rs2 = reg.find(split_result[2])->second;

    result.push_back(func7);
    result.push_back(rs2);
    result.push_back(rs1);
    result.push_back(func3);
    result.push_back(rd);
    result.push_back(opcode);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }

    return result;
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
        map<int, vector<string>> seperate_results;

        //store one instruction
        vector<string> split_result;


        for (int i = 0; i < instruction.size(); i++) {
            // seperate instruction and define each section of instruction
            //    check if is the jump instruction that previos instruction has use
            split_result = split(instruction[i], ':');
            if (split_result[0] != instruction[i]) {
                if (jump.find(split_result[0]) != jump.end()) {
                    int temp = jump.find(split_result[0])->second;
                    seperate_results.find(temp)->second.push_back(to_string(i));
                }
                split_result.erase(split_result.begin());
            }

            // example:
            // add x0,x0,x0 
            // split_result[0] =add  split_result[1]=x0,x0,x0
            split_result = split(split_result[0],' ');
            
            int index = stoi(instructionTemplate.find(split_result[0])->second[1]);
            vector<string> tempV;
            // translate into binary code
            switch (index) {
            case 0:
                //for add/sub
                tempV = decode1(split_result);
                break;
            case 1: break;
            }
           
            
            seperate_results.insert({ i,tempV });

        }

        return s;
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    };
}