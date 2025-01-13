#include "InstructionSet.h"

InstructionSet::InstructionSet() {
    _instructions = {
        // ALU Commands
   /*   COMMAND  | TYPE  | OPCODE | OPERAND COUNT  */
        {"ADD",  {0b0000,     0b000001,   3}}, 
        {"SUB",  {0b0000,     0b000010,   3}},
        {"AND",  {0b0000,     0b000011,   3}},
        {"OR",   {0b0000,     0b000100,   3}},
        {"XOR",  {0b0000,     0b000101,   3}},
        {"NOT",  {0b0000,     0b000111,   3}},
        // Shift Commands
        {"SHL",  {0b0001,     0b000001,   3}},
        {"SHR",  {0b0001,     0b000010,   3}},
        {"ROL",  {0b0001,     0b000011,   3}},
        {"ROR",  {0b0001,     0b000100,   3}},
        // Memory Operations
        {"JMP",  {0b0010,     0b000001,   1}},
        {"LOAD", {0b0010,     0b000010,   2}},
        {"STORE",{0b0010,     0b000011,   2}},
        // Branch Commands
        {"BEQ",  {0b0011,     0b000001,   3}},
        {"BNE",  {0b0011,     0b000010,   3}},
        {"BLT",  {0b0011,     0b000011,   3}},
        {"BGT",  {0b0011,     0b000100,   3}},
        // Jump Commands 
        
        {"CALL", {0b0100,     0b000010,   1}},
        {"RET",  {0b0100,     0b000011,   0}},
        // Comparision commands
        {"CMP",  {0b0101,     0b000001,   2}},
        // Immediate Commands
        {"MOVI", {0b0110,     0b000001,   2}},
    };
}

InstructionInfo InstructionSet::getInstruction(const std::string& command) const 
{
    if (_instructions.find(command) == _instructions.end()) 
    {
        throw std::runtime_error("Unknown command: " + command);
    }
    return _instructions.at(command);
}

bool InstructionSet::isValidCommand(const std::string& command) const 
{
    return _instructions.find(command) != _instructions.end();
}
