#include "BinaryGenerator.h"
#include <bitset>
#include <stdexcept>



BinaryGenerator::BinaryGenerator(SymbolTable& symTable) : symbolTable(symTable) {}

std::string BinaryGenerator::generate_bin_single_instr(const Instruction& instr) const 
{
    std::bitset<64> binary;

    
    return binary.to_string();
}


std::string BinaryGenerator::encodeInstructionType(const std::string& istr_type) const 
{
    if (istr_type == "ALU"      )      return "0000";
    if (istr_type == "SHIFT"    )      return "0001";
    if (istr_type == "MEM"      )      return "0010";
    if (istr_type == "BRANCH"   )      return "0011";
    if (istr_type == "JUMP"     )      return "0100"; 
    if (istr_type == "CMP"      )      return "0101";
    if (istr_type == "CMP"      )      return "0110";
    throw std::runtime_error("Unknown instruction type: " + istr_type);
}

