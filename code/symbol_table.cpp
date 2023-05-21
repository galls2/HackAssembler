//
// Created by USER on 15/05/2023.
//

#include "symbol_table.h"

SymbolTable::SymbolTable() {
    initialize_symbol_table();
}

void SymbolTable::initialize_symbol_table() {
    for (uint8_t i = 0; i <= s_max_logical_register_num; ++i)
    {
        _table.emplace("R"+std::to_string(i), i);
    }

    _table.emplace("SCREEN", s_screen_symbol_value);
    _table.emplace("KBD", s_keyboard_symbol_value);
    _table.emplace("SP", s_sp_symbol_value);
    _table.emplace("LCL", s_lcl_symbol_value);
    _table.emplace("ARG", s_arg_symbol_value);
    _table.emplace("THIS", s_this_symbol_value);
    _table.emplace("THAT", s_that_symbol_value);
}

bool SymbolTable::add_symbol(std::string symbol, const uint16_t value) {
    return _table.emplace(std::move(symbol), value).second;
}

std::optional<uint16_t> SymbolTable::get(const std::string& symbol) const {
    if (_table.find(symbol) == _table.end()) {
        return {};
    }

    return {_table.at(symbol)};
}
