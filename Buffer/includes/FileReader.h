#ifndef FILE_READER_H_
#define FILE_READER_H_

#include "LibConstants.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

class FileReader{
public:
    FileReader(const char* filePath);
    ~FileReader();
    char* getNextFileBlock();
    bool isEof();
private:
    ifstream* readFile;
    char* blockContent;
    int currentCharIndex;
    bool eof;
};
#endif
