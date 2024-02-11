#ifndef HEADER_BUS
#define HEADER_BUS
#include <memory>

#include "dram.h"
//cpu communication to IO device
//Like memory and keyboard screen ..
class Bus {
public:
    Bus();
    template<typename T>
    T load(u64 addr){
        //address mapped from dram
        if(addr>=DRAM_BASE && addr <= DRAM_END){
            return _ram->load<T>(addr);
        }
        return 0;
    }
    template<BUS_VALID T>
    void store(u64 addr,T data){
        if(addr>=DRAM_BASE && addr <= DRAM_END){
            return _ram->store<T>(addr,data);
        }
    }

    void LoadProgram(const char* filename);
private:
    std::shared_ptr<Dram> _ram;
};


#endif // !BUS_HADER
