#include "symbolic_command_translator.h"

#include <bitset>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <algorithm>

std::string SymbolicCommandTranslator::translate_symbolic_command(ParsedAsmLine parsed_line, SymbolTable& symbol_table) {
    assert(!parsed_line.empty());

    switch (parsed_line[0]) {
        case '@': { // A-instruction
            return handle_a_instruction(parsed_line, symbol_table);
        }
        default: { // C-instruction
            return handle_c_instruction(parsed_line);
        }
    }
}

std::string SymbolicCommandTranslator::handle_a_instruction(std::string unparsed_a_instruction, SymbolTable& symbol_table) {
    unparsed_a_instruction.erase(0, 1);

    uint16_t a_instruction_value;

    const auto symbol_table_translation = symbol_table.get(unparsed_a_instruction);
    if (symbol_table_translation) { // label declaration or symbol that is already defined
        a_instruction_value = *symbol_table_translation;
    }
    else if (!std::all_of(unparsed_a_instruction.begin(), unparsed_a_instruction.end(), [](const auto& ch) { return std::isdigit(ch) != 0; }))
    {   // valid variable declaration - a symbol
        a_instruction_value = _next_var_address;
        ++_next_var_address;
        symbol_table.add_symbol(unparsed_a_instruction, a_instruction_value);
    }
    else { // this is a pure address
        try {
            a_instruction_value = std::stoi(unparsed_a_instruction);
        }
        catch (const std::invalid_argument &e) {
            std::cerr << "Invalid A-instruction: " << unparsed_a_instruction
                      << ". Failed to convert the string after @ to a number. Aborting." << std::endl;
            return "";
        }
        catch (const std::out_of_range &e) {
            std::cerr << "Invalid A-instruction: " << unparsed_a_instruction
                      << ". Converted number is too large. Aborting." << std::endl;
            return "";
        }
    }

    return std::bitset<16>(a_instruction_value).to_string();
}

std::string SymbolicCommandTranslator::handle_c_instruction(std::string unparsed_c_instruction) {
    std::string binary_c_cmd = "111";

    const size_t equality_pos = unparsed_c_instruction.find('=');
    const std::string dest_str = (equality_pos == std::string::npos) ? "" : unparsed_c_instruction.substr(0, equality_pos);

    const size_t semicolon_pos = unparsed_c_instruction.find(';');
    const size_t comp_start_index = (equality_pos == std::string::npos) ? 0 : (equality_pos + 1);
    const std::string comp_str = unparsed_c_instruction.substr(comp_start_index, semicolon_pos);
    const std::string jump_str = (semicolon_pos == std::string::npos) ? "" : unparsed_c_instruction.substr(semicolon_pos + 1);

    const bool comp_part_res = convert_string_to_binary_encoding(comp_str, _symbolic_comp_to_binary, "computation", binary_c_cmd);
    if (!comp_part_res) return "";

    const bool dest_part_res = convert_string_to_binary_encoding(dest_str, _symbolic_dest_to_binary, "destination", binary_c_cmd);
    if (!dest_part_res) return "";

    const bool jump_part_res = convert_string_to_binary_encoding(jump_str, _symbolic_jump_to_binary, "jump", binary_c_cmd);
    if (!jump_part_res) return "";

    return binary_c_cmd;
}

bool SymbolicCommandTranslator::convert_string_to_binary_encoding(const std::string& symbolic_key,
                                                                  const std::map<std::string, std::string>& symbolic_mapping,
                                                                  const std::string& symbolic_meaning_description,
                                                                  std::string& binary_command_to_build) {
    const auto binary_encoding = symbolic_mapping.find(symbolic_key);
    if (binary_encoding == symbolic_mapping.end())
    {
        std::cerr << "Invalid C-instruction. The " << symbolic_meaning_description << " part " << symbolic_key << " is illegal." << std::endl;
        return false;
    }

    binary_command_to_build += binary_encoding->second;
    return true;
}
const std::map<std::string, std::string> SymbolicCommandTranslator::_symbolic_jump_to_binary =
        {
                {"", "000"},
                {"JGT", "001"},
                {"JEQ", "010"},
                {"JGE", "011"},
                {"JLT", "100"},
                {"JNE", "101"},
                {"JLE", "110"},
                {"JMP", "111"}
        };


const std::map<std::string, std::string> SymbolicCommandTranslator::_symbolic_dest_to_binary =
        {
                {"", "000"},
                {"M", "001"},
                {"D", "010"},
                {"MD", "011"},
                {"A", "100"},
                {"AM", "101"},
                {"AD", "110"},
                {"AMD", "111"}
        };

const std::map<std::string, std::string> SymbolicCommandTranslator::_symbolic_comp_to_binary =
        {
                {"0", "0101010"},
                {"1", "0111111"},
                {"-1", "0111010"},

                {"D", "0001100"},
                {"A", "0110000"},
                {"M", "1110000"},

                {"!D", "0001101"},
                {"!A", "0110001"},
                {"!M", "1110001"},

                {"-D", "0001111"},
                {"-A", "0110011"},
                {"-M", "1110011"},

                {"D+1", "0011111"},
                {"A+1", "0110111"},
                {"M+1", "1110111"},

                {"D-1", "0001110"},
                {"A-1", "0110010"},
                {"M-1", "1110010"},

                {"D+A", "0000010"},
                {"D+M", "1000010"},

                {"D-A", "0010011"},
                {"D-M", "1010011"},

                {"A-D", "0000111"},
                {"M-D", "1000111"},

                {"D&A", "0000000"},
                {"D&M", "1000000"},

                {"D|A", "0010101"},
                {"D|M", "1010101"}
        };

