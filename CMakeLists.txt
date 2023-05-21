cmake_minimum_required(VERSION 3.20)
project(HackAssembler)

set(CMAKE_CXX_STANDARD 17)

add_executable(HackAssembler code/main.cpp code/hack_assembler.cpp code/asm_file_parser.cpp code/symbolic_command_translator.cpp code/symbol_table.cpp)
