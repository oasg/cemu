#ifndef HEADER_CPU
#define HEADER_CPU
#include "bus.h"

class CPU{
    public:
        explicit CPU(std::shared_ptr<Bus> bus);
        ~CPU();
        void run();
        void dump_regs();
        u64* get_regs(){ return regs; }
        //execute one instruction
        void step();
    private:
        //get instruction
        //The length of the instruction is 32 bits
        unsigned int fetch();
        //execute instruction
        void execute(unsigned int inst);
    private:
        //RISC-V has 32 registers
        u64 regs[32];
        u64 pc;
        std::shared_ptr<Bus> _bus;
};

#endif // !HEADER_CPU