#include <iostream>
#include "cpu.h"


int main(int, char**){
    CPU cpu;
    cpu.load_program("../tests/sample.bin");
    cpu.run();
    cpu.dump_regs();
    return 0;
}
