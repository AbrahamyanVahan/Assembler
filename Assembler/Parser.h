#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "InstructionSet.h" 
#include "SymbolTable.h"    
#include "Tokenizer.h"     
#include "Instruction.h"    

class Parser {
private:
    InstructionSet& instructionSet; 
    SymbolTable& symbolTable;       

public:
    // Constructor
    Parser(InstructionSet& instSet, SymbolTable& symTable);
    std::vector<Instruction> parseProgram(const std::vector<std::vector<Token>>& tokenizedProgram) const;
    Instruction parseLine(const std::vector<Token>& tokens) const;
    void validateOperandCount(const std::string& opcode, size_t operandCount) const;
};

#endif // PARSER_H
