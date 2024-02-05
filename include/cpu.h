#ifndef HEADER_CPU
#define HEADER_CPU 
#include <memory>
#define DRAM_SIZE 1024*1024*128
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