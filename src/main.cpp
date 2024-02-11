#include <iostream>
#include "cpu.h"
#include "spdlog/spdlog.h"
void init_log(){
    //spdlog::set_pattern( "[%n] [%l] %v");
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Debug mode");
#elif
    spdlog::set_level(spdlog::level::warn);
    spdlog::info("Release mode");
#endif
}
int main(int, char**){
    std::shared_ptr<Bus> bus = std::make_shared<Bus>();
    bus->LoadProgram("../tests/add-addi.bin");
    CPU cpu(bus);
    init_log();
    cpu.run();
    cpu.dump_regs();
    return 0;
}
