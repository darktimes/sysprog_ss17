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

class Buffer {
public:
	Buffer(const char* filePath);

	//esli vidumivaesh huetu, please default constructor dlya ludej, sps @ Serega
	Buffer(const char* filePath, bool isReadBuffer);
	virtual ~Buffer();
    char getChar();
    void ungetChar(int returnIndex);
    int getCurrentLine() const;
    int getCurrentPos() const;
private:
    void readNextBufferBlock();
    void clearNextBufferBlock();
    FileReader* fileReader;
    int currentCharIndex;
    int currentBlockIndex;
    bool isReadBuffer;
    const char* filePath;
    char* bufferArray[BufferConstants::BUFFER_BLOCKS_NUMBER-1];
    
};

#endif /* BUFFER_H_ */
