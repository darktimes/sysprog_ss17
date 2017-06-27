#pragma once

#include <string.h>
#include <iostream>
#include <fstream>

#include "Buffer.h"
#include "BufferBlock.h"

class BufferBlock;

class FileReader{
public:
    FileReader(const char* filePath);
    ~FileReader();
    bool isOpen();
    BufferBlock* getBufferBlockAt(unsigned int blockIndex);

private:
    std::ifstream* readFile;
	std::streambuf* strBuffer;
    bool opened;
};
