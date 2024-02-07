//
// Created by gou ruibo on 2024/02/07.
//

#ifndef TYPE_H
#define TYPE_H
typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

template<typename T>
concept BUS_VALID = (
            std::is_same_v<T, u64> ||
            std::is_same_v<T, u32> ||
            std::is_same_v<T, u16> ||
            std::is_same_v<T, u8>
        );
#define DRAM_SIZE 1024*1024*128
const u64 DRAM_BASE = 0x80000000;  //same as qemu
const u64 DRAM_END = DRAM_SIZE+DRAM_BASE - 1;
#endif //TYPE_H
