#ifndef ASM_FILE_READER_H
#define ASM_FILE_READER_H

#include <string>
#include <vector>

class AsmFileReader {

public:
    
    AsmFileReader(const std::string& filePath);
    void readFile();
    const std::vector<std::string>& getLines() const;
    void clear();

private:
    std::vector<std::string> _lines;
    std::string _filePath;

};

#endif // ASM_FILE_READER_H
