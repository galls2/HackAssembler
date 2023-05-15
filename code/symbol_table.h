#pragma once

#include <map>
#include <string>

class SymbolTable {
public:
    SymbolTable();
    SymbolTable(const SymbolTable&) = delete;
    SymbolTable(SymbolTable&&) = default;
    SymbolTable& operator=(const SymbolTable& other) = delete;
    SymbolTable& operator=(SymbolTable&& other) = default;

    bool add_symbol(const std::string& symbol, const uint16_t value);

private:
    void initialize_symbol_table();

    static constexpr uint16_t s_max_logical_register_num = 15;

    static constexpr uint16_t s_screen_symbol_value = 16384;
    static constexpr uint16_t s_keyboard_symbol_value = 24576;
    static constexpr uint16_t s_sp_symbol_value = 0;
    static constexpr uint16_t s_lcl_symbol_value = 1;
    static constexpr uint16_t s_arg_symbol_value = 2;
    static constexpr uint16_t s_this_symbol_value = 3;
    static constexpr uint16_t s_that_symbol_value = 4;

    std::map<std::string, uint16_t> _table;
};
