cmake_minimum_required(VERSION 3.20)
project(HackAssembler)

set(CMAKE_CXX_STANDARD 14)

add_executable(HackAssembler main.cpp hack_assembler.cpp hack_assembler.h asm_file_parser.cpp asm_file_parser.h symbolic_command_translator.cpp symbolic_command_translator.h hack_assembler_common.h)
