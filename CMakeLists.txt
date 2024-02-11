cmake_minimum_required(VERSION 3.20.0)
project(gemu VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
enable_testing()
add_subdirectory(third_party/spdlog)

include_directories(include)
add_executable(gemu src/main.cpp src/cpu.cpp
        src/dram.cpp
        src/bus.cpp


)
target_compile_definitions(gemu
        PRIVATE
        # If the debug configuration pass the DEBUG define to the compiler
        $<$<CONFIG:Debug>:DEBUG>
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(gemu  spdlog::spdlog)

#testing
add_subdirectory(third_party/googletest)
add_subdirectory(tests)