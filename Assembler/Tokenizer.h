#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

// Token structure
struct Token {
    std::string type;  // COMMAND, REGISTER, IMMEDIATE, MEMORY,   LABEL_DEF, LABEL_REF
    std::string value; // "ADD",    "R1",     "#10", "MEM[0x100]", "START"
};

class Tokenizer {
public:
    
    std::vector<Token> tokenize_line_of_asm_code(const std::string& line) const;
    std::vector<std::vector<Token>> tokenizeProgram(const std::vector<std::string>& program) const;
};

#endif // TOKENIZER_H
