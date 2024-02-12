#include "cpu.h"
#include <cstdint>
#include <cstring>
#include <ios>
#include "type.h"
#include <spdlog/spdlog.h>

const char *REG_NAME[] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

CPU::CPU(std::shared_ptr<Bus> bus) : pc(DRAM_BASE), _bus(bus)
{
    memset(regs, 0, sizeof(regs[0]) * 32);
}

CPU::~CPU()
{
}

unsigned int CPU::fetch()
{
    return _bus->load<u32>(pc);
}
void CPU::execute(unsigned int inst)
{
    // op code is always 6bit
    u32 opcode = inst & 0x7f;
    u32 funct7,rs2,rs1,funct3,rd,imm;
    spdlog::debug("inst: 0x{:x}", inst);
    switch (opcode)
    {
    case 0b0110011: // add rd,rs1,rs2
        // R-Type
        rd = ((inst >> 7)) & 0x1f;
        rs1 = ((inst >> 15)) & 0x1f;
        rs2 = ((inst >> 20)) & 0x1f;
        funct3 = ((inst >> 12)) & 0x7;
        funct7 = ((inst >> 25)) & 0x7f;
        regs[rd] = regs[rs1] + regs[rs2];
        switch (funct3)
        {
        case 0x0:
            if(funct7 == 0x0){
                //add:  rd = rs1 + rs2
                regs[rd] = regs[rs1] + regs[rs2];
            }
            if(funct7 == 0x20){
                //sub:  rd = rs1 - rs2
                regs[rd] = regs[rs1] - regs[rs2];
            } 
            break;
        case 0x1:
            //shift left logical
            //sll: rd = rs1 << rs2
            regs[rd] = regs[rs1] << regs[rs2];
            break;;
        case 0x2:
            //set less than
            //slt: rd = (rs1 < rs2)?1:0
            regs[rd] = (regs[rs1] <  regs[rs2])?1:0;
            break;
        case 0x3:
            //set more than(zero-extends)
            // sltu: rd = (rs1 < rs2)?1:0
            regs[rd] = (regs[rs1] <  regs[rs2])?1:0;
            break;
        case 0x4:
            //xor: rd = rs1 ^ rs2
            regs[rd] = regs[rs1] ^ regs[rs2];
            break;
        case 0x5:
            if(funct7 == 0x0){  //logical
                //srl:  rd = rs1 >> rs2
                regs[rd] = regs[rs1] >> regs[rs2];
            }
            if(funct7 == 0x20){  //arithmetic
                //sra:  rd = rs1 >> rs2
                regs[rd] = (long)regs[rs1] >> regs[rs2];
            }
            break;
        case 0x6:
            //or: rd = rs1 | rs2
            regs[rd] = regs[rs1] | regs[rs2];
            break;
        case 0x7:
            //and: rd = rs1 & rs2
            regs[rd] = regs[rs1] & regs[rs2];
            break;
        default:
            spdlog::error("Unsupported instruction: 0x{:x}, opcode: 0d{:b}", inst, opcode);
            break;
        }

        break;
    case 0b0011011:
        //I-type
        rd = ((inst >> 7)) & 0x1f;

        // addiw rd,rs1,immediate
        imm = inst >> 20;
        regs[rd] = regs[rs1] + imm;
        rs1 = ((inst >> 15)) & 0x1f;
        break;
    case 0b0000011:
        //I-type 
        //load instructions
        funct3 = ((inst >> 12)) & 0x7;
        rs1 = ((inst >> 15)) & 0x1f;
        rd = ((inst >> 7)) & 0x1f;
        imm = inst >> 20;
        switch (funct3)
        {
        case 0x0:
            //lb byte
            regs[rd] = _bus->load<u8>(rs1 + imm);
            break;
        case 0x1:
            //lh half
            regs[rd] = _bus->load<u16>(rs1 + imm);
            break;
        case 0x2:
            //lw word
            regs[rd] = _bus->load<u32>(rs1 + imm);
            break;
        case 0b11:
            //ld double words
            regs[rd] = _bus->load<u64>(rs1 + imm);
            break;
        default:
            spdlog::error("Unsupported instruction: 0x{:x}, opcode: 0d{:b}", inst, opcode);
            break;  
        break;
        }
    case 0b0100011:
        //store instructions
        break;
    case 0b0000000: // nop
        break;
    default:
        spdlog::error("Unsupported instruction: 0x{:x}, opcode: 0d{:b}", inst, opcode);
        break;
    }
}
void CPU::dump_regs()
{
    spdlog::info("registers:");
    for (int i = 0; i < 32; i++)
    {
        spdlog::info("x{}: 0x{:x}", i, regs[i]);
    }
}

void CPU::run()
{
    while (pc < DRAM_BASE + 20)
    {
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
