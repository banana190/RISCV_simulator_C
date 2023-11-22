#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <string>
#include "Decode.h"
#include "execution.h"
#include "Memory.h"
#include "Writeback.h"
using std::queue;
using std::string;
using std::vector;
extern vector<uint8_t> memory;
extern vector<uint32_t> registers;

pair<bool, int> hazard_checker(vector<Instruction> pipelining)
{
    for (int i = 0; i < pipelining.size(); i++)
    {
        if (pipelining[i].kind == "7" && i <= 2)
            return make_pair(true, i); // branch will stall 3 cycles
        string rd = pipelining[i].rd;
        for (int j = 0; j < i; j++)
        {
            string rs1 = pipelining[j].rs1;
            string rs2 = pipelining[j].rs2;
            if (rd == rs1 || rd == rs2)
                return make_pair(true, i);
        }
    }
    return make_pair(false, -1);
}
vector<Instruction> run_pipelining(vector<Instruction> instructions, vector<Instruction> pipelining, int cycle)
{
    auto [hazard, location] = hazard_checker(pipelining);
    if (hazard)
        cout << "hazard detected\n";
    else
        pipelining.insert(pipelining.begin(), instructions[cycle]); // this line has a bug WIP
    if (pipelining.size() >= 5 && location < 4)
    {
        switch (std::stoi(pipelining[4].kind))
        {
        case 1:
            Add_wb(pipelining[4]);
            break;
        case 2:
            Sub_wb(pipelining[4]);
            break;
        case 3:
            Addi_wb(pipelining[4]);
            break;
        case 4:
            Mul_wb(pipelining[4]);
            break;
        case 5:
            Lw_wb(pipelining[4]);
            break;
        case 6:
            Sw_wb(pipelining[4]);
            break;
        case 7:
            Beq_wb(pipelining[4]);
            break;
        case 8:
            Lui_wb(pipelining[4]);
            break;
        case 9:
            And_wb(pipelining[4]);
            break;
        case 10:
            Andi_wb(pipelining[4]);
            break;
        case 11:
            Or_wb(pipelining[4]);
            break;
        case 12:
            Ori_wb(pipelining[4]);
            break;
        case 13:
            Sll_wb(pipelining[4]);
            break;
        case 14:
            Srl_wb(pipelining[4]);
            break;
        case 15:
            Slti_wb(pipelining[4]);
            break;
        case 16:
            Sltiu_wb(pipelining[4]);
            break;
        }
        pipelining[5] = pipelining[4];
    }
    if (pipelining.size() >= 4 && location < 3)
    {
        switch (std::stoi(pipelining[3].kind))
        {
        case 5:
            pipelining[3].LMD = Lw_mem(pipelining[3]);
            break;
        case 6:
            Sw_mem(pipelining[3]);
            break;
        case 7:
            pipelining[3].LMD = Beq_mem(pipelining[3]);
            break;
        }
        pipelining[4] = pipelining[3];
    }
    if (pipelining.size() >= 3 && location < 2)
    {
        switch (std::stoi(pipelining[2].kind))
        {
        case 1:
            pipelining[2].ALUOutput = Add_ex(pipelining[2]);
            break;
        case 2:
            pipelining[2].ALUOutput = Sub_ex(pipelining[2]);
            break;
        case 3:
            pipelining[2].ALUOutput = Addi_ex(pipelining[2]);
            break;
        case 4:
            pipelining[2].mul_ALUOutput = Mul_ex(pipelining[2]);
            break;
        case 5:
            pipelining[2].ALUOutput = Lw_ex(pipelining[2]);
            break;
        case 6:
            pipelining[2].ALUOutput = Sw_ex(pipelining[2]);
            break;
        case 7:
            pipelining[2].ALUOutput = Beq_ex(pipelining[2]);
            break;
        case 8:
            pipelining[2].ALUOutput = Lui_ex(pipelining[2]);
            break;
        case 9:
            pipelining[2].ALUOutput = And_ex(pipelining[2]);
            break;
        case 10:
            pipelining[2].ALUOutput = Andi_ex(pipelining[2]);
            break;
        case 11:
            pipelining[2].ALUOutput = Or_ex(pipelining[2]);
            break;
        case 12:
            pipelining[2].ALUOutput = Ori_ex(pipelining[2]);
            break;
        case 13:
            pipelining[2].ALUOutput = Sll_ex(pipelining[2]);
            break;
        case 14:
            pipelining[2].ALUOutput = Srl_ex(pipelining[2]);
            break;
        case 15:
            pipelining[2].ALUOutput = Slti_ex(pipelining[2]);
            break;
        case 16:
            pipelining[2].ALUOutput = Sltiu_ex(pipelining[2]);
            break;
        }
        pipelining[3] = pipelining[2];
    }
    if (!hazard)
    {
        if (pipelining.size() >= 3)
            pipelining[2] = pipelining[1];
        pipelining[1] = pipelining[0];
    }
    if (pipelining.size() >= 6)
        pipelining.erase(pipelining.begin() + 5);
    return pipelining;
}