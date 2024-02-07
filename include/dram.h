//
// Created by oasg on 2024/02/07.
//

#ifndef DRAM_H
#define DRAM_H
#include "type.h"
class Dram {
public:
    Dram(u32 n_of_bytes);
    ~Dram();
    template<BUS_VALID T>
    T load(u64 addr);
    template<BUS_VALID T>
    T store(u64 addr,T data);
private:
    u8* _dram;
};



#endif //DRAM_H
