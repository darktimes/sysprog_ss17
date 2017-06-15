
#pragma once

#include <stdlib.h>

#include "FileReader.h"
#include "BufferBlock.h"

class FileReader;
class BufferBlock;

class Buffer {
public:

    Buffer(const char*);
	virtual ~Buffer();
    char getChar();
    void ungetChar(unsigned int);

    unsigned int getCurrentLine();
    unsigned int getCurrentPos();

    static const unsigned int BLOCK_SIZE;
	static const unsigned int MAX_STEPBACK;

	bool isEOF();
	bool isNoFile();

private:
	bool eofConsumed;
	bool noFile;
    FileReader* fileReader;
    BufferBlock* currentBufferBlock;
    void switchToNextBlock();
    void adjustIndiciesIn(int steps);
    unsigned int currentCharIndex;
    unsigned int currentBlockIndex;
    unsigned int stepBackAmount;
};
