#pragma once

#include <vector>
#include <string>

class ParsedAsmLine {
public:
    ParsedAsmLine() = default;
    ParsedAsmLine(const ParsedAsmLine&) = delete;
    ParsedAsmLine& operator=(const ParsedAsmLine&) = delete;
    ParsedAsmLine(ParsedAsmLine&&) = default;
    ParsedAsmLine& operator=(ParsedAsmLine&&) = default;

    void add_part(std::string&& part) { _parts.emplace_back(std::move(part)); };

    const std::vector<std::string>& get_parts() const { return _parts; }

    virtual ~ParsedAsmLine() = default;

private:
    std::vector<std::string> _parts;
};

using ParsedAsmLines = std::vector<ParsedAsmLine>;