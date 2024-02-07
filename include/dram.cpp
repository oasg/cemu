//
// Created by oasg on 2024/02/07.
//

#include "dram.h"
<<<<<<< HEAD


=======
>>>>>>> e03168f (add test framework)
Dram::Dram(u32 n_of_bytes) {
    _dram = new u8[n_of_bytes];
}

Dram::~Dram() {
    delete[] _dram;
}

template<BUS_VALID T>
T Dram::load(u64 addr) {
<<<<<<< HEAD
    int uBytes = sizeof(T)/8;


}
=======
    u8 uBytes = sizeof(T)/8;
    T result;
    u64 index = (addr-DRAM_BASE);
    for(int i = 0 ;i<uBytes;i++) {
        result|= _dram[index+i]<<i*8;
    }
    return result;
}

template<BUS_VALID T>
void Dram::store(u64 addr, T data) {

}
>>>>>>> e03168f (add test framework)
