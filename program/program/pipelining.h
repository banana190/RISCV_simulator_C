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
#include "Display.h"
using std::queue;
using std::string;
using std::vector;
extern vector<uint8_t> memory;
extern vector<uint32_t> registers;

pair<bool, int> hazard_checker(vector<Instruction> pipelining)
{
    for (int i = pipelining.size() - 1; i >= 0; i--)
    {
        if (pipelining[i].kind == "7")
            return make_pair(true, i - 1); // branch will stall 3 cycles
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
    if (pipelining.size() >= 6)
        pipelining.erase(pipelining.begin() + 5);
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
        if (location >= 1) // insert bubble into ex location
            pipelining.insert(pipelining.begin() + 2, bubble);
    }

    // if the hazard instruction is not at decode location, we still can fetch new instructions
    if (pipelining[0].nextInstruction != nullptr && !first && location < 1) // if there is still have instructions, fetch it.
    {
        pipelining.insert(pipelining.begin(), *(pipelining[0].nextInstruction));
    }
    else if (pipelining[0].nextInstruction == nullptr && location < 1) // if there is no instruction, insert bubble
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
            if (pipelining[4].ALUOutput == 1)
            {
                pipeline_print(pipelining);
                int LMD = pipelining[4].LMD;
                int size = pipelining.size();
                for (int i = 0; i < size; i++)
                {
                    pipelining.erase(pipelining.begin());
                }
                pipelining.push_back(instructions[LMD]);
                for (int i = 0; i < 4; i++)
                {
                    pipelining.push_back(bubble);
                }
            }
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
    return pipelining;
}
// single processing
Instruction run_one_inst(Instruction instructions)
{
    switch (std::stoi(instructions.kind))
    {
    case 1:
        instructions.ALUOutput = Add_ex(instructions);
        Add_wb(instructions);
        break;
    case 2:
        instructions.ALUOutput = Sub_ex(instructions);
        Sub_wb(instructions);
        break;
    case 3:
        instructions.ALUOutput = Addi_ex(instructions);
        Addi_wb(instructions);
        break;
    case 4:
        instructions.mul_ALUOutput = Mul_ex(instructions);
        Mul_wb(instructions);
        break;
    case 5:
        instructions.ALUOutput = Lw_ex(instructions);
        instructions.LMD = Lw_mem(instructions);
        Lw_wb(instructions);
        break;
    case 6:
        instructions.ALUOutput = Sw_ex(instructions);
        Sw_mem(instructions);
        Sw_wb(instructions);
        break;
    case 7:
        instructions.ALUOutput = Beq_ex(instructions);
        if (instructions.ALUOutput == 1)
        {
        }
        instructions.LMD = Beq_mem(instructions);
        Beq_wb(instructions);

        break;
    case 8:
        instructions.ALUOutput = Lui_ex(instructions);
        Lui_wb(instructions);
        break;
    case 9:
        instructions.ALUOutput = And_ex(instructions);
        And_wb(instructions);
        break;
    case 10:
        instructions.ALUOutput = Andi_ex(instructions);
        Andi_wb(instructions);
        break;
    case 11:
        instructions.ALUOutput = Or_ex(instructions);
        Or_wb(instructions);
        break;
    case 12:
        instructions.ALUOutput = Ori_ex(instructions);
        Ori_wb(instructions);
        break;
    case 13:
        instructions.ALUOutput = Sll_ex(instructions);
        Sll_wb(instructions);
        break;
    case 14:
        instructions.ALUOutput = Srl_ex(instructions);
        Srl_wb(instructions);
        break;
    case 15:
        instructions.ALUOutput = Slti_ex(instructions);
        Slti_wb(instructions);
        break;
    case 16:
        instructions.ALUOutput = Sltiu_ex(instructions);
        Sltiu_wb(instructions);
        break;
    }
    return instructions;
}