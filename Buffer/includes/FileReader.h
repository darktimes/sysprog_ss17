#pragma once

#include <string.h>
#include <iostream>
#include <fstream>

#include "Buffer.h"

class FileReader{
public:
    FileReader(const char* filePath);
    ~FileReader();
    char* getNextFileBlock();
    bool isEof();
private:
    std::ifstream* readFile;
    char* blockContent;
    int currentCharIndex;
    bool eof;
};
