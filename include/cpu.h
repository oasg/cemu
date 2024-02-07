#ifndef HEADER_CPU
#define HEADER_CPU
#include "bus.h"

class CPU{
    public:
        CPU();
        ~CPU();
        void run();
        void step();
        void load_program(const char* filename);
        void dump_regs();
        long* get_regs(){ return regs; }
    private:
        //get instruction
        //The length of the instruction is 32 bits
        unsigned int fetch();
        //execute instruction
        void execute(unsigned int inst);
    private:
        //RISC-V has 32 registers
        long regs[32];
        unsigned long pc;
        char* dram;
};

#endif // !HEADER_CPU