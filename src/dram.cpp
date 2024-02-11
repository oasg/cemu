//
// Created by oasg on 2024/02/07.
//

#include "dram.h"
#include <fstream>
#include "spdlog/spdlog.h"
Dram::Dram() {
    _dram = new u8[DRAM_SIZE];
}

Dram::~Dram() {
    delete[] _dram;
}

void Dram::load_program(const char* filename){
    //spdlog::info("Loading program: {}", filename);
    std::ifstream file;
    file.open(filename, std::ios::binary | std::ios::in);
    if(!file.is_open()){
        spdlog::critical("Failed to open file: {}", filename);
        return;
    }
    file.seekg(0,std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    if(file.read((char*)_dram, size)){
        spdlog::info("Read {} bytes from {}", size, filename);
    }else
    {
        spdlog::critical("Failed to read file: {}", filename);
    }
    file.close();
}

