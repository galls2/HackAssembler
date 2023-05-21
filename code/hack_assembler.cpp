#include "hack_assembler.h"
#include "symbol_table.h"

#include <fstream>
#include <iostream>
#include <cassert>

void HackAssembler::assemble(const std::string &asm_path, const std::string& out_path)
{
    std::optional<std::ofstream> out_stream = open_output_file(out_path);
    if (!out_stream)
    {
        return;
    }

    ParsedAsmLines parsed_asm_lines = _asm_file_parser.parse(asm_path);
    if (parsed_asm_lines.empty())
    {
        return;
    }

    SymbolTable symbol_table;
    extract_label_definitions(parsed_asm_lines, symbol_table);

    SymbolicCommandTranslator translator;

    for (auto&& parsed_asm_line: parsed_asm_lines) {
        const std::string translated_cmd = translator.translate_symbolic_command(std::move(parsed_asm_line), symbol_table);
        if (translated_cmd.empty()) return; // Error in translation, aborting
        (*out_stream) << translated_cmd << std::endl;
    }

    out_stream->close();
}

std::optional<std::ofstream> HackAssembler::open_output_file(const std::string& out_path) {
    std::ofstream out_stream;
    out_stream.open(out_path);
    if (!out_stream.is_open())
    {
        std::cerr << "Error opening output file " << out_path << ". Aborting." << std::endl;
        return {};
    }

    return out_stream;
}

void HackAssembler::extract_label_definitions(ParsedAsmLines& parsed_asm_lines, SymbolTable& symbol_table) {

    uint16_t next_line_no = 0;
    auto iter = parsed_asm_lines.begin();

    while (iter != parsed_asm_lines.end())
    {
        assert(!iter->empty());
        if ((*iter)[0] == '(') // corresponds to a label definition
        {
            std::string& label_line = *iter;
            assert(label_line[label_line.size() - 1] == ')');

            // removing ( and )
            label_line.erase(0, 1);
            label_line.pop_back();

            symbol_table.add_symbol(std::move(label_line), next_line_no);
            iter = parsed_asm_lines.erase(iter);
        }
        else
        {
            ++iter;
            ++next_line_no;
        }
    }
}
