#pragma once

#include <string>
#include "hack_assembler_common.h"

class SymbolicCommandTranslator {
public:
    SymbolicCommandTranslator() = default;
    std::string translate_symbolic_command(const ParsedAsmLine& parsed_line);
};