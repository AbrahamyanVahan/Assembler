#include "Parser.h"
#include <stdexcept>


Parser::Parser(InstructionSet& instSet, SymbolTable& symTable)
    : instructionSet(instSet), symbolTable(symTable) {}


std::vector<Instruction> Parser::parseProgram(const std::vector<std::vector<Token>>& tokenizedProgram) const {
    std::vector<Instruction> instructions;

    for (const auto& line_tokens : tokenizedProgram) {
        if (line_tokens.empty()) {
            continue; // Skip empty lines
        }
        if (line_tokens[0].type == "LABEL_DEF") {
            // Skip label definitions
            continue;
        }
        instructions.push_back(parseLine(line_tokens));
    }

    return instructions;
}


Instruction Parser::parseLine(const std::vector<Token>& tokens) const {
    if (tokens.empty()) {
        throw std::runtime_error("Empty line detected during parsing");
    }

    if (tokens[0].type != "COMMAND") {
        throw std::runtime_error("Line must begin with a command: " + tokens[0].value);
    }

    
    auto info = instructionSet.getInstruction(tokens[0].value);

    
    validateOperandCount(tokens[0].value, tokens.size() - 1);

    
    Instruction instr;
    instr.istr_type = info.type;
    instr.opcode = info.opcode;

    // Parse operands based on instruction type
    if (info.type == 0b000000 || info.type == 0b0001) /*--ALU--*/  // 3 operand requering instructions
    {
        
        // ALU instructions (ADD R1, R2, R3)
        // source_1 need to be register always
        if (tokens[1].type == "REGISTER") 
        {
            instr.source1 = tokens[1].value;    // Source1 register
        }
        else 
        {
            throw std::runtime_error("Invalid Source_1" + tokens[1].value +
                ": expected Register number like R1, R2 ... " +  +
                ", got " + tokens[1].value);
        }
        // source_2
        if (tokens[2].type == "REGISTER") 
        {
            instr.source2 = tokens[2].value;    // Source2 register
            instr.source2_type = "REGISTER";
        }
        else if (tokens[2].type == "IMMIDIATE")
        {
            instr.source2 = tokens[2].value;    // Source2 IMMMIDATE
            instr.source2_type = "IMMIDIATE";
        }
        else if (tokens[2].type == "MEMORY") 
        {
            instr.source2 = tokens[2].value;    // Source2 MEMORY
            instr.source2_type = "MEMORY";
        }
        // destination
        if (tokens[3].type == "REGISTER")
        {
            instr.source2 = tokens[3].value;    // dest register
            instr.source2_type = "REGISTER";
        }
        else if (tokens[3].type == "MEMORY")
        {
            instr.source2 = tokens[3].value;    // dest MEMORY
            instr.source2_type = "MEMORY";
        }
        else if (tokens[2].type == "IMMIDIATE")
        {
            throw std::runtime_error("Invalid destination" + tokens[3].value +
                ": expected Register number like R1, R2 ... or MEM ADDRESS " + +
                ", got " + tokens[3].value);
        }
 
    }
    else if (info.type == 0b0010) // MEMORY OPERATIONS REQUIRES 2 OPERANDS for JMP 1 operands
    { 
        // Memory instructions (e.g., LOAD R1, MEM[0x100])
        if (tokens[0].value != "JMP" ) {
            if (tokens[0].value == "LOAD") 
            {
                if (tokens[1].type == "REGISTER")
                {
                    instr.destination = tokens[1].value;    // Source1 register
                    instr.dest_type = "REGISTER";
                }
                else
                {
                    throw std::runtime_error("Invalid Destination" + tokens[1].value +
                        ": expected Register number like R1, R2 ... " + +
                        ", got " + tokens[1].value);
                }
                if (tokens[2].type == "MEMORY")
                {
                    instr.source1 = "DONT_CARE";    // Source1 not important
                    instr.source2 = tokens[2].value; // source 
                    instr.source2_type = "MEMORY";
                }
                else
                {
                    throw std::runtime_error("Invalid OPERAND" + tokens[2].value +
                        ": expected Mem Address number" + +
                        ", got " + tokens[2].value);
                }
            }
            else if (tokens[0].value == "STORE") 
            {
                if (tokens[1].type == "REGISTER")
                {
                    instr.destination = tokens[1].value;    // Source1 register
                    instr.dest_type = "REGISTER";
                }
                else
                {
                    throw std::runtime_error("Invalid Destination" + tokens[1].value +
                        ": expected Register number like R1, R2 ... " + 
                        ", got " + tokens[1].value);
                }
                if (tokens[2].type == "MEMORY") 
                {
                    instr.destination = tokens[2].value;
                    instr.dest_type = "MEMORY";
                }
                else 
                {
                    throw std::runtime_error("Invalid OPERAND" + tokens[2].value +
                        ": expected Mem Address number" + 
                        ", got " + tokens[2].value);
                }
            }
        }
        else // JMP 
        {
            instr.destination = tokens[1].value;
            instr.dest_type = "MEMORY";
            instr.source1 = "DONT CARE";
            instr.source2 = "DONT CARE";
            instr.source2_type = "DONT CARE";
        }
    }
   
    // sharunakeli
    if (instr.dest_type == "MEMORY" && instr.source2_type == "MEMORY") 
    {
        instr.requires_simplification = true;
    }
    return instr;
}


// Validate the operand count for a command
void Parser::validateOperandCount(const std::string& opcode, size_t operandCount) const {
    auto info = instructionSet.getInstruction(opcode);
    if (operandCount != info.operands) {
        throw std::runtime_error("Invalid operand count for " + opcode +
            ": expected " + std::to_string(info.operands) +
            ", got " + std::to_string(operandCount));
    }
}
