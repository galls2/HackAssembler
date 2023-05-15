#include "hack_assembler.h"

#include <fstream>
#include <iostream>

void HackAssembler::assemble(const std::string &asm_path, const std::string& out_path)
{
    std::ofstream out_stream;
    out_stream.open(out_path);
    if (!out_stream.is_open())
    {
        std::cerr << "Error opening output file " << out_path << ". Aborting." << std::endl;
        return;
    }

    ParsedAsmLines parsed_asm_lines = _asm_file_parser.parse(asm_path);
    if (parsed_asm_lines.empty())
    {
        return;
    }

    for (auto&& parsed_asm_line: parsed_asm_lines) {
        std::string translated_cmd = SymbolicCommandTranslator::translate_symbolic_command(std::move(parsed_asm_line));
        if (translated_cmd.empty()) return; // Error in translation, aborting
        out_stream << translated_cmd << std::endl;
    }

    out_stream.close();
}