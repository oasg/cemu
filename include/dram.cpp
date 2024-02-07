//
// Created by oasg on 2024/02/07.
//

#include "dram.h"


Dram::Dram(u32 n_of_bytes) {
    _dram = new u8[n_of_bytes];
}

Dram::~Dram() {
    delete[] _dram;
}

template<BUS_VALID T>
T Dram::load(u64 addr) {
    int uBytes = sizeof(T)/8;


}