#include "AsmFileReader.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

AsmFileReader::AsmFileReader(const std::string& filePath) : _filePath(filePath) {}

void AsmFileReader::readFile() 
{
    std::ifstream file(_filePath);

    if (!file.is_open()) 
    {
        throw std::runtime_error("Error: Unable to open assembly file: " + _filePath);
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        // Optionally, trim the line or handle comments here
        _lines.push_back(line);
    }

    file.close();
}

const std::vector<std::string>& AsmFileReader::getLines() const 
{
    return _lines;
}

void AsmFileReader::clear() {
    _lines.clear();
}
