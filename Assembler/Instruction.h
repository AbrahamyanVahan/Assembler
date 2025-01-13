#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

// Instruction structure 64 bit 
typedef struct Instruction {
    std::string istr_type;            // ALU, SHIFT, MEM, ...                    - 4 bits
    std::string opcode;              //  ADD, SUB ........                       - 6 bits
    std::string source1;             // Source 1 operand (always register)       - 5 bits
    std::string source2_type;        // Source 2 type (register, imme, mem)      - 2 bits
    std::string source2;             // Source 2 operand                     (16 bits, if reg 5 LSBs)
    std::string dest_type;           // Destination type (register or memory)    - 1 bit
    std::string destination;         // Destination operand                   (16 bits, if reg 5 LSBs)
    // other 14 bits unused 
    bool requires_simplification = false; // Flag for memory operations requiring LOAD
} Instruction;

#endif // INSTRUCTION_H