#include "bus.h"

Bus::Bus() {
    _ram = std::make_shared<Dram>();

}

void Bus::LoadProgram(const char *filename) {
    _ram->load_program(filename);
}
