#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include "Decode.h"
#include "execution.h"
#include "Memory.h"
#include "Writeback.h"
using std::queue;
using std::string;
using std::vector;
extern vector<uint8_t> memory;
extern vector<uint32_t> registers;

vector<Instruction> run_pipelining(vector<Instruction> instructions, vector<Instruction> pipelining, int cycle)
{
    pipelining.insert(pipelining.begin(), instructions[cycle]);
    if (pipelining[2].instruction_name != "")
    {
        switch (pipelining[2].kind)
        {
        case 1:
            pipelining[2].ALUOutput = Add_ex(pipelining[2]);
        case 2:
            pipelining[2].ALUOutput = Sub_ex(pipelining[2]);
        case 3:
            pipelining[2].ALUOutput = Addi_ex(pipelining[2]);
        case 4:
            pipelining[2].mul_ALUOutput = Mul_ex(pipelining[2]);
        case 5:
            pipelining[2].ALUOutput = Lw_ex(pipelining[2]);
        case 6:
            pipelining[2].ALUOutput = Sw_ex(pipelining[2]);
        case 7:
            pipelining[2].ALUOutput = Beq_ex(pipelining[2]);
        case 8:
            pipelining[2].ALUOutput = Lui_ex(pipelining[2]);
        case 9:
            pipelining[2].ALUOutput = And_ex(pipelining[2]);
        case 10:
            pipelining[2].ALUOutput = Andi_ex(pipelining[2]);
        case 11:
            pipelining[2].ALUOutput = Or_ex(pipelining[2]);
        case 12:
            pipelining[2].ALUOutput = Ori_ex(pipelining[2]);
        case 13:
            pipelining[2].ALUOutput = Sll_ex(pipelining[2]);
        case 14:
            pipelining[2].ALUOutput = Srl_ex(pipelining[2]);
        case 15:
            pipelining[2].ALUOutput = Slti_ex(pipelining[2]);
        case 16:
            pipelining[2].ALUOutput = Sltiu_ex(pipelining[2]);
        }
    }
    if (pipelining[3].instruction_name != "")
    {
        switch (pipelining[3].kind)
        {
        case 5:
            pipelining[3].LMD = Lw_mem(pipelining[3]);
        case 6:
            pipelining[3].LMD = Sw_mem(pipelining[3]);
        case 7:
            pipelining[3].LMD = Beq_mem(pipelining[3]);
        }
    }
    if (pipelining[4].instruction_name != "")
    {
        switch (pipelining[4].kind)
        {
        case 1:
            Add_wb(pipelining[4]);
        case 2:
            Sub_wb(pipelining[4]);
        case 3:
            Addi_wb(pipelining[4]);
        case 4:
            Mul_wb(pipelining[4]);
        case 5:
            Lw_wb(pipelining[4]);
        case 6:
            Sw_wb(pipelining[4]);
        case 7:
            Beq_wb(pipelining[4]);
        case 8:
            Lui_wb(pipelining[4]);
        case 9:
            And_wb(pipelining[4]);
        case 10:
            Andi_wb(pipelining[4]);
        case 11:
            Or_wb(pipelining[4]);
        case 12:
            Ori_wb(pipelining[4]);
        case 13:
            Sll_wb(pipelining[4]);
        case 14:
            Srl_wb(pipelining[4]);
        case 15:
            Slti_wb(pipelining[4]);
        case 16:
            Sltiu_wb(pipelining[4]);
        }
    }
}