#pragma once

#include <string>
#include <vector>

#include "hack_assembler_common.h"

class AsmFileParser {
    AsmFileParser() = default;
    std::vector<ParsedAsmLine> parse(const std::string& asm_file_path);
};
