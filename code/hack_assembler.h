#pragma once

#include <string>

class HackAssembler {
public:
    HackAssembler() = default;
    void assemble(const std::string& asm_path, const std::string out_path);
};

