#include "asm_file_parser.h"

#include <fstream>
#include <sstream>
#include <iostream>

ParsedAsmLines AsmFileParser::parse(const std::string& asm_file_path) {
    std::ifstream file_reader;
    file_reader.open(asm_file_path.data());
    if (!file_reader.is_open()) {
        std::cerr << "Error while opening file " << asm_file_path << std::endl;
        return {};
    }

    std::vector<ParsedAsmLine> parsed_asm_lines;

    std::string read_line;
    while (getline(file_reader, read_line)) {
        ParsedAsmLine parsed_line = parse_file_line(std::move(read_line));
        parsed_asm_lines.emplace_back(std::move(parsed_line));
    }

    file_reader.close();
    return parsed_asm_lines;
}

ParsedAsmLine AsmFileParser::parse_file_line(std::string unparsed_file_line) {
    ParsedAsmLine parsed_line;

    const size_t comment_start_pos = unparsed_file_line.find("//");
    if (comment_start_pos != std::string::npos)
    {
        unparsed_file_line = unparsed_file_line.substr(0, comment_start_pos);
    }

    std::istringstream iss(unparsed_file_line);
    std::string temp_line_part;
    while (getline( iss, temp_line_part, ' '))
    {
        if (!temp_line_part.empty()) parsed_line.add_part(std::move(temp_line_part));
    }

    return parsed_line;
}
