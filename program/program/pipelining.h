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
    for (int i = pipelining.size() - 1; i >= 0; i--)
    {
        if (pipelining[i].kind == "7" && i <= 2)
            return make_pair(true, i); // branch will stall 3 cycles
        string rd = pipelining[i].rd;
        for (int j = i - 1; j >= 1; j--)
        {
            string rs1 = pipelining[j].rs1;
            string rs2 = pipelining[j].rs2;
            if (rd == rs1 && rd != "" || rd == rs2 && rd != "")
                return make_pair(true, j);
        }
    }
    return make_pair(false, -1);
}
vector<Instruction> run_pipelining(vector<Instruction> instructions, vector<Instruction> pipelining)
{
    bool first = false;
    Instruction bubble;
    bubble.kind = "17"; // empty kind
    // this is fetching the first instruction
    if (pipelining.empty())
    {
        pipelining.push_back(instructions[0]);
        first = true;
    }

    auto [hazard, location] = hazard_checker(pipelining);
    // if there is a hazard on location 2:stall until the hazard gone
    if (hazard)
    {
        cout << "hazard detected\n";
        if (location >= 1)
            pipelining.insert(pipelining.begin() + 2, bubble);
    }

    if (pipelining[0].nextInstruction != nullptr && !first && location < 1)
    {
        pipelining.insert(pipelining.begin(), *(pipelining[0].nextInstruction));
    }
    else if (pipelining[0].nextInstruction == nullptr && location < 1)
    {
        pipelining.insert(pipelining.begin(), bubble);
    }

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
    }
    if (pipelining.size() >= 6)
        pipelining.erase(pipelining.begin() + 5);
    return pipelining;
}
// single processing
vector<Instruction> run_one_inst(vector<Instruction> instructions, vector<Instruction> pipelining)
{
    Instruction bubble;
    bubble.kind = "17"; // empty kind
    if (pipelining.empty())
    {
        pipelining.push_back(instructions[0]);
    }
    else
    {
        pipelining.insert(pipelining.begin(), bubble);
    }

    if (pipelining.size() >= 5)
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
    }
    if (pipelining.size() >= 4)
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
    }
    if (pipelining.size() >= 3)
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
    }
    if (pipelining.size() >= 6)
        pipelining.erase(pipelining.begin() + 5);
    return pipelining;
}