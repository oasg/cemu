#include "cpu.h"
#include <cstdint>
#include <cstring>
#include <ios>
#include "type.h"
#include <spdlog/spdlog.h>

const char* REG_NAME[] = {     
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", 
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", 
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", 
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

CPU::CPU(std::shared_ptr<Bus> bus): pc(DRAM_BASE),_bus(bus) {
    memset(regs, 0, sizeof(regs[0])*32);
}

CPU::~CPU() {

}

unsigned int CPU::fetch() {
    return _bus->load<u32>(pc);
}
void CPU::execute(unsigned int inst){
    //op code is always 6bit
    unsigned int opcode = inst&0x7f;
    //R-Type
    unsigned int rd = ((inst>>7))&0x1f;
    unsigned int rs1 = ((inst>>15))&0x1f;
    unsigned int rs2 = ((inst>>20))&0x1f;
    unsigned int funct3 = ((inst>>12))&0x7;
    unsigned int funct7 = ((inst>>25))&0x7f;
    unsigned int imm = 0;
    spdlog::debug("inst: 0x{:x}", inst);

    switch(opcode){
        case 0b0011011:   //addiw rd,rs1,immediate
            imm = inst>>20;
            regs[rd] = regs[rs1] + imm;
            break;
        case 0b0110011:     //add rd,rs1,rs2
            regs[rd] = regs[rs1] + regs[rs2];
            break;
        case 0b0000000:     //nop
            break;
        default:
            spdlog::error("Unsupported instruction: 0x{:x}, opcode: 0d{:b}", inst,opcode);
            break;
    }
}
void CPU::dump_regs(){
    spdlog::info("registers:");
    for(int i = 0; i < 32; i++){
        spdlog::info("x{}: 0x{:x}", i, regs[i]);
    }
}

void CPU::run(){
    while(pc < DRAM_BASE+20){
        auto inst = fetch();
        execute(inst);
        pc += 4;
    }
}

void CPU::step()
{
    auto inst = fetch();
    execute(inst);
    pc += 4;
}
