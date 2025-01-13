#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <unordered_map>
#include <string>
#include <stdexcept>

struct InstructionInfo {
    uint8_t type;       // Instruction type 
    uint8_t opcode;    
    uint8_t operands;   // Number of operands required
};

class InstructionSet {

public:
    InstructionSet();
    InstructionInfo getInstruction(const std::string& command) const;
    bool isValidCommand(const std::string& command) const;

private:
    std::unordered_map<std::string, InstructionInfo> _instructions;

};

#endif
