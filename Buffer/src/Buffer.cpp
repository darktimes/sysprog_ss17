/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"


Buffer::Buffer(const char* filePath, bool isRead) {
    this->filePath = filePath;
    this->isReadBuffer = isRead;
    this->fileReader = new FileReader(this->filePath);
    currentBlockIndex = 0;
    currentCharIndex = 0;
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}


char Buffer::getChar()
{
    if (currentCharIndex >= BufferConstants::BUFFER_BLOCK_SIZE)
    {
        currentBlockIndex = (currentBlockIndex + 1)%BufferConstants::BUFFER_BLOCKS_NUMBER;
        readNextBufferBlock();  
        currentCharIndex = 0; 
    } 
    
    return (char) bufferArray[currentBlockIndex][currentCharIndex++];
}

void Buffer::ungetChar(int returnIndex)
{
    
}

void Buffer::readNextBufferBlock()
{
    bufferArray[currentBlockIndex] = fileReader->getNextBlock();
    clearNextBufferBlock();
}
void Buffer::clearNextBufferBlock(){
    int clearBlockIndex = (currentBlockIndex + 1)%BufferConstants::BUFFER_BLOCKS_NUMBER;
    
    free(bufferArray[clearBlockIndex]);
    bufferArray[clearBlockIndex] = 0;
}


