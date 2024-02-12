#include <gtest/gtest.h>
#include "cpu.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(TestInst, ADD){
    std::shared_ptr<Bus> bus = std::make_shared<Bus>();
    bus->LoadProgram("../../tests/add-addi.bin");
    CPU cpu(bus);
    cpu.run();
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[29], 0x5);
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[30], 0x25);
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[31], 0x2a);
}

TEST(TestInst, RTYPE){
    std::shared_ptr<Bus> bus = std::make_shared<Bus>();
    bus->LoadProgram("../../tests/r-type.bin");
    CPU cpu(bus);
    cpu.run();
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[29], 5);
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[30], 37);
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[31], 42);
    //sub
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[1], 37);
    //xor
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[2], cpu.get_regs()[31] ^ cpu.get_regs()[29]);
    //or
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[3], cpu.get_regs()[31] | cpu.get_regs()[29]);
    //and
    cpu.step();
    EXPECT_EQ(cpu.get_regs()[4], cpu.get_regs()[31] & cpu.get_regs()[29]);

}