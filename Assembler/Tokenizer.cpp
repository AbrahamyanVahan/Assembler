#include "Tokenizer.h"
#include <regex>
#include <sstream>
#include <stdexcept>

// Tokenize a single line of assembly code
std::vector<Token> Tokenizer::tokenize_line_of_asm_code(const std::string& line) const 
{
    std::vector<Token> tokens;
    std::istringstream stream(line);
    std::string word;

    while (stream >> word) {
        if (std::regex_match(word, std::regex("[A-Z]+"))) 
        {
            tokens.push_back({ "COMMAND", word });
        }
        else if (std::regex_match(word, std::regex("R[0-9]+"))) 
        {
            tokens.push_back({ "REGISTER", word });
        }
        else if (std::regex_match(word, std::regex("#-?[0-9]+|#0x[0-9A-Fa-f]+"))) // can be hex as well 
        {
            tokens.push_back({ "IMMEDIATE", word });
        }
        else if (std::regex_match(word, std::regex("MEM\\[0x[0-9A-Fa-f]+\\]"))) 
        {
            tokens.push_back({ "MEMORY", word });
        }
        else if (std::regex_match(word, std::regex("[A-Za-z_][A-Za-z0-9_]*:"))) 
        {
            tokens.push_back({ "LABEL_DEF", word.substr(0, word.size() - 1) });
        }
        else if (std::regex_match(word, std::regex("[A-Za-z_][A-Za-z0-9_]*"))) 
        {
            tokens.push_back({ "LABEL_REF", word });
        }
        else if (word == ",") 
        {
            continue; // Skip 
        }
        else {
            throw std::runtime_error("Unknown token: " + word);
        }
    }

    return tokens;
}

// Tokenize entire program
std::vector<std::vector<Token>> Tokenizer::tokenizeProgram(const std::vector<std::string>& program) const 
{
    std::vector<std::vector<Token>> tokenizedProgram;

    for (const auto& line : program) 
    {
        tokenizedProgram.push_back(tokenize_line_of_asm_code(line));
    }

    return tokenizedProgram;
}
