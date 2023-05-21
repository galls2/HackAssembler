#pragma once

#include <map>

#include "hack_assembler_common.h"
#include "symbol_table.h"

class SymbolicCommandTranslator {
public:
    SymbolicCommandTranslator() = default;
    std::string translate_symbolic_command(ParsedAsmLine parsed_line, SymbolTable& symbol_table);

private:
    static bool convert_string_to_binary_encoding(const std::string& symbolic_key, const std::map<std::string, std::string>& symbolic_mapping, const std::string& symbolic_meaning_description, std::string& binary_command_to_build);

    std::string handle_a_instruction(std::string unparsed_a_instruction, SymbolTable& symbol_table);
    static std::string handle_c_instruction(std::string unparsed_c_instruction);

    static const std::map<std::string, std::string> _symbolic_jump_to_binary;
    static const std::map<std::string, std::string> _symbolic_comp_to_binary;
    static const std::map<std::string, std::string> _symbolic_dest_to_binary;

    uint16_t _next_var_address = s_first_var_address;

    static constexpr uintptr_t s_first_var_address = 16;
};