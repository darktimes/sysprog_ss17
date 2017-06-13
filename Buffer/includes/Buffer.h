/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#pragma once

#include <stdlib.h>

#include "FileReader.h"
#include "BufferBlock.h"

class FileReader;
class BufferBlock;

class Buffer {
public:

    Buffer(const char*);
	Buffer(const char*, bool);
	virtual ~Buffer();
    char getChar();
    void ungetChar(unsigned int);
    unsigned int getCurrentPos();

    static const unsigned int  BUFFER_BLOCK_SIZE;
	static const unsigned int  BUFFER_MAX_STEPBACK;


private:
    FileReader* fileReader;
    BufferBlock* currentBufferBlock;
    void switchToNextBlock();

    unsigned int currentCharIndex;
    unsigned int currentBlockIndex;

    unsigned int currentPos;
    bool isReadBuffer;
};
