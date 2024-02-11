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