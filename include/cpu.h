#ifndef HEADER_CPU
#define HEADER_CPU 
#include <memory>
#define DRAM_SIZE 1024*1024*128

const char* REG_NAME[] = {     
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", 
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", 
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", 
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

class CPU{
    public:
        CPU();
        ~CPU();

        //get instruction
        //The length of the instruction is 32 bits
        int fetch();
        //
        void execute(int inst);
    private:
        //RISC-V has 32 registers
        long regs[32];
        long pc;
        char* dram;
};

#endif // !HEADER_CPU