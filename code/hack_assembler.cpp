#include <iostream>

#include "hack_assembler.h"

void HackAssembler::assemble(const std::string &asm_path, const std::string& out_path)
{
    const ParsedAsmLines parsed_asm_lines = _asm_file_parser.parse(asm_path);
    if (parsed_asm_lines.empty())
    {
        return;
    }

    std::cout << "Assembled LOL" << std::endl;
}
