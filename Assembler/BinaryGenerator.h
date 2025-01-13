#ifndef BINARYGENERATOR_H
#define BINARYGENERATOR_H

#include <string>
#include "Instruction.h"
#include "SymbolTable.h"

class BinaryGenerator {

public:
    
    BinaryGenerator(SymbolTable& symTable);

    std::string generate_bin_single_instr(const Instruction& instr) const;
private:
    SymbolTable& symbolTable; 

    
    std::string encodeInstructionType(const std::string& istr_type) const;
    std::string encodeOpcode(const std::string& opcode) const;
    std::string encodeRegister(const std::string& reg) const;
    std::string encodeImmediate(const std::string& imm) const;
    std::string encodeMemory(const std::string& mem) const;

};

#endif // BINARYGENERATOR_H
