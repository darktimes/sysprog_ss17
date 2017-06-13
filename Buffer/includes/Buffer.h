/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdlib.h>

#include "LibConstants.h"
#include "FileReader.h"
#include "BufferBlock.h"

class Buffer {
public:

    Buffer(const char*);
	Buffer(const char*, bool);
	virtual ~Buffer();
    char getChar();
    void ungetChar(unsigned int);
    unsigned int getCurrentPos();

private:
    FileReader* fileReader;
    BufferBlock* currentBufferBlock;
    void switchToNextBlock();

    unsigned int currentCharIndex;
    unsigned int currentBlockIndex;

    unsigned int currentPos;
    bool isReadBuffer;
};

#endif /* BUFFER_H_ */
