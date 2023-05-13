#pragma once

#include "hack_assembler_common.h"

class AsmFileParser {
public:
    AsmFileParser() = default;
    ParsedAsmLines parse(const std::string& asm_file_path);

private:
    static ParsedAsmLine parse_file_line(std::string unparsed_file_line);
};
