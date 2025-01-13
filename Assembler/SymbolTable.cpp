#include "SymbolTable.h"

void SymbolTable::addSymbol(const std::string& label, uint64_t address) 
{
    if (_table.find(label) != _table.end()) 
    {
        throw std::runtime_error("Duplicate label definition: " + label);
    }
    _table[label] = address;
}

uint64_t SymbolTable::getAddress(const std::string& label) const 
{
    if (_table.find(label) == _table.end()) 
    {
        throw std::runtime_error("Undefined label: " + label);
    }
    return _table.at(label);
}

bool SymbolTable::contains(const std::string& label) const 
{
    return _table.find(label) != _table.end();
}
