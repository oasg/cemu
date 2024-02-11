//
// Created by oasg on 2024/02/07.
//

#ifndef DRAM_H
#define DRAM_H
#include "type.h"
class Dram {
public:
    Dram();
    ~Dram();
    void load_program(const char* filename);
    template<BUS_VALID T>
    inline T load(u64 addr){
        {
            u8 uBytes = sizeof(T);
            T result = 0;
            u64 index = (addr-DRAM_BASE);
            for(int i = 0 ;i<uBytes;i++) {
                result|= _dram[index+i]<<i*8;
            }
            return result;
        }
    }
    template<BUS_VALID T>
    void store(u64 addr, T data) {
        u8 uBytes = sizeof(T)/8;
        u64 index = (addr-DRAM_BASE);
        for(int i = 0 ;i<uBytes;i++) {
            _dram[index+i] = data>>i*8;
        }
    }

private:

    u8* _dram;
};



#endif //DRAM_H
