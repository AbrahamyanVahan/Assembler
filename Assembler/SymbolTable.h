#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <stdexcept>

class SymbolTable {

public:
    void addSymbol(const std::string& label, uint64_t address);
    uint64_t getAddress(const std::string& label) const;
    bool contains(const std::string& label) const;
private:
    std::unordered_map<std::string, uint64_t> _table;

};

#endif
