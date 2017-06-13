/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Buffer.h"

const unsigned int Buffer::BUFFER_BLOCK_SIZE = 6;
const unsigned int Buffer::BUFFER_MAX_STEPBACK = Buffer::BUFFER_BLOCK_SIZE / 2;


Buffer::Buffer(const char* filePath) {
    isReadBuffer = true;
    fileReader = new FileReader(filePath);
    currentBlockIndex = 0;
    currentCharIndex = 0;
    currentPos = 0;
    currentBufferBlock = nullptr;
}


Buffer::Buffer(const char* filePath, bool isRead):Buffer(filePath) {
    isReadBuffer = isRead;
}

Buffer::~Buffer() {
    //TODO
}

char Buffer::getChar()
{       
    if (!currentBufferBlock) //not valid
    {
        currentBufferBlock = new BufferBlock(fileReader->getNextFileBlock());
    } 
    else 
    {
        if (currentCharIndex >= (Buffer::BUFFER_BLOCK_SIZE / 2))
        {
            if (currentCharIndex == Buffer::BUFFER_BLOCK_SIZE)
            {
                switchToNextBlock();
            }
            else 
            {   
                if (currentBufferBlock->getPrevious()) 
                {                  
                    currentBufferBlock->clearPrevious();
                }
                if (!currentBufferBlock->getNext() && !fileReader->isEof())
                {
                    currentBufferBlock->setNext(new BufferBlock(fileReader->getNextFileBlock()));
                }
            }
        }
    }
    char out = currentBufferBlock->getCharAt(currentCharIndex++);
    if (out == '\0')
    {
        if (fileReader->isEof())
        {
            currentPos++;
            return '\0';
        }
        else
        {
            switchToNextBlock();
            currentPos++;
            return currentBufferBlock->getCharAt(currentCharIndex++);
        }
    }
    
    currentPos++;
    return out;
}

void Buffer::ungetChar(unsigned int ungetCount)
{
    if (ungetCount> Buffer::BUFFER_MAX_STEPBACK)
        throw std::runtime_error("Error: stepback is too big");
        
    if (!currentBufferBlock) //not valid
    {
        throw std::runtime_error("Error: current block not initialized");
    }
    
    if (ungetCount <=  currentCharIndex)
    {
        currentCharIndex -= ungetCount;
        currentPos -= ungetCount;
    }
    else
    { //not tested
        if (currentBufferBlock->getPrevious())
        {
            int diff = ungetCount - currentCharIndex;
            currentBufferBlock = currentBufferBlock->getPrevious();
            currentBlockIndex--;
            currentCharIndex = currentBufferBlock->getLength() - diff;
        }
        else
            throw std::runtime_error("Error: previous block does not exist yet");
    }
        
}
void Buffer::switchToNextBlock(){
    currentBufferBlock = currentBufferBlock->getNext();
    currentCharIndex = 0;
    currentBlockIndex++;
}

unsigned int Buffer::getCurrentPos(){
    return currentPos;
}
