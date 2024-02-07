#!/bin/bash

files=$(find . -maxdepth 1 -name "*.s")

for file in $files; do
    filename=$(basename -- "$file")
    filename="${filename%.*}"

    riscv64-unknown-elf-gcc -O0 -Wl,-Ttext=0x0 -nostdlib -o --target=riscv64 -march=rv64g -mno-relax -o $filename.o $file
    if [ $? -eq 0 ]; then
        echo "Compilation of $file succeeded."
    else
        echo "Compilation of $file failed."
    fi

    riscv64-unknown-elf-objcopy -O binary $filename.o $filename.bin
    if [ $? -eq 0 ]; then
        echo "objcopy of $file succeeded."
    else
        echo "objcopy of $file failed."
    fi
done
