#include "cpu.h"
#include <cstdint>
#include <cstring>
#include <ios>
#include "type.h"
#ifdef LOG

#endif // DEBUG
#include <spdlog/spdlog.h>

#include <fstream>

const char* REG_NAME[] = {     
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", 
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", 
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", 
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

CPU::CPU(): pc(0) {
    memset(regs, 0, sizeof(regs[0])*32);
    dram = new char[DRAM_SIZE];
}

CPU::~CPU() {
    delete [] dram;
}

unsigned int CPU::fetch() {
    unsigned int b1 = dram[pc]&0xff;
    unsigned int b2 = dram[pc+1]&0xff;
    unsigned int b3 = dram[pc+2]&0xff;
    unsigned int b4 = dram[pc+3]&0xff;
    unsigned int inst = b1 | b2<<8 | b3<<16 | b4<<24;
    return inst;
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
    spdlog::info("inst: 0x{:x}", inst);

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
void CPU::load_program(const char* filename){
    //spdlog::info("Loading program: {}", filename);
    std::ifstream file;
    file.open(filename, std::ios::binary | std::ios::in);
    if(!file.is_open()){
        spdlog::error("Failed to open file: {}", filename);
        return;
    }
    file.seekg(0,std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    if(file.read(dram, size)){
        spdlog::info("Read {} bytes from {}", size, filename);
    }else
    {
        spdlog::error("Failed to read file: {}", filename);
    }
    file.close();
}
void CPU::run(){
    while(pc < 20){
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
