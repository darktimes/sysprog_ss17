#ifndef FILE_READER_H_
#define FILE_READER_H_

#include "LibConstants.h"
#include <iostream>
#include <fstream>
using namespace std;

class FileReader{
public:
    FileReader(const char* filePath);
    ~FileReader();
    char* getNextBlock();
    
private:
    fstream* readFile;
    char* blockContent;
    const char* filePath;
    int currentIndex;
};
#endif
