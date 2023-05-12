cmake_minimum_required(VERSION 3.20)
project(HackAssembler)

set(CMAKE_CXX_STANDARD 14)

add_executable(HackAssembler main.cpp HackAssembler.cpp HackAssembler.h AsmFileParser.cpp AsmFileParser.h)
