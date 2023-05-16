#pragma once

#include "asm_file_parser.h"
#include "symbolic_command_translator.h"
#include "symbol_table.h"

class HackAssembler {
public:
    HackAssembler() = default;
    void assemble(const std::string& asm_path, const std::string& out_path);

private:
    AsmFileParser _asm_file_parser;
    SymbolicCommandTranslator _sym_cmd_translator;

    static std::optional<std::ofstream> open_output_file(const std::string& out_path);

    static void extract_label_definitions(ParsedAsmLines& parsed_asm_lines, SymbolTable& symbol_table);
};

