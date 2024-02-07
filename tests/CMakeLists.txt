
add_executable(instruction_test instruction_test.cpp ../src/cpu.cpp)
target_link_libraries(instruction_test GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(instruction_test)

target_link_libraries(instruction_test  spdlog::spdlog)