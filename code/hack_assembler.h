#pragma once

#include "asm_file_parser.h"
#include "symbolic_command_translator.h"

class HackAssembler {
public:
    HackAssembler() = default;
    void assemble(const std::string& asm_path, const std::string& out_path);

private:
    AsmFileParser _asm_file_parser;
    SymbolicCommandTranslator _sym_cmd_translator;
};

