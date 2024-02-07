#ifndef HEADER_BUS
#define HEADER_BUS
#include <memory>

#include "dram.h"
//cpu communication to IO device
//Like memory and keyboard screen ..
class Bus {
public:
    Bus();
    u64 load(u64 addr,u64 size);
    u64 store(u64 addr,u64 size);
private:
    std::shared_ptr<Dram> _ram;
};


#endif // !BUS_HADER
