#include "cpu.h"
#include <cstdint>
#include <cstring>
#include <spdlog/spdlog.h>

CPU::CPU(): pc(0) {
    memset(regs, 0, 32);
    dram = new char[DRAM_SIZE];
}

CPU::~CPU() {
    delete [] dram;
}

int CPU::fetch() {
    long inst = dram[pc]|(dram[pc+1]<<8)|dram[pc+2]<<16|dram[pc+2]<<24;
    return inst;
}
void CPU::execute(int inst){
    //op code is always 6bit
    int opcode = inst&0x7f;
    //R-Type
    int rd = ((inst>>7))&0x1f;
    int rs1 = ((inst>>15))&0x1f;
    int rs2 = ((inst>>20))&0x1f;
    int funct3 = ((inst>>12))&0x7;
    int funct7 = ((inst>>25))&0x7f;
    int imm = 0;
    switch(opcode){
        case 0b0001011:   //addi rd,rs1,immediate
            imm = (inst>>20);
            regs[rd] = regs[rs1] + imm;
            break;
        case 0b0110011:     //add rd,rs1,rs2
            regs[rd] = regs[rs1] + regs[rs2];
            break; 

        default:
            spdlog::error("Unsupported instruction: 0x{:x}", inst);
            break;
    }
}