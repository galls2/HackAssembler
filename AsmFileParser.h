#pragma once

#include <string>
#include <vector>

struct ParsedAsmLine {


};

class AsmFileParser {
    AsmFileParser() = default;
    std::vector<ParsedAsmLine> parse(const std::string& asm_file_path);
};
