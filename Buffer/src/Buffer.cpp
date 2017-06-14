/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Buffer.h"

const unsigned int Buffer::BLOCK_SIZE = 16;
const unsigned int Buffer::MAX_STEPBACK = Buffer::BLOCK_SIZE / 2;


Buffer::Buffer(const char* filePath) {
    fileReader = new FileReader(filePath);
    currentBlockIndex = 0;
    currentCharIndex = 0;
    stepBackAmount = 0;
    currentBufferBlock = nullptr;
    eofConsumed = false;
}

Buffer::~Buffer() {
	if (currentBufferBlock) {
		delete currentBufferBlock;
	}
	delete fileReader;
}

char Buffer::getChar()
{       
	if (eofConsumed) {
		return '\0';
	}

    if (!currentBufferBlock) {
        currentBufferBlock = fileReader->getBufferBlockAt(currentBlockIndex);
        if (!currentBufferBlock) {
        	eofConsumed = true;
        	return '\0';
        }
    }

	if (currentCharIndex == MAX_STEPBACK) {
		if (currentBufferBlock->getPrevious()) {
			currentBufferBlock->clearPrevious();
		}
	}

	if (currentCharIndex == BLOCK_SIZE - MAX_STEPBACK) {
		if (!currentBufferBlock->isLastBlock()) {
			currentBufferBlock->setNext(fileReader->getBufferBlockAt(currentBlockIndex + 1));
		}
	} else if (currentCharIndex == BLOCK_SIZE) {
		currentCharIndex = 0;
		currentBlockIndex++;
		if (currentBufferBlock->getNext()) {
			currentBufferBlock = currentBufferBlock->getNext();
		}

	}

	if (stepBackAmount < MAX_STEPBACK) {
		stepBackAmount++;
	}
	char c = currentBufferBlock->getCharAt(currentCharIndex++);
	if (c == '\0') {
		eofConsumed = true;
	}
	return c;
}

void Buffer::ungetChar(unsigned int ungetCount)
{
    if (ungetCount > Buffer::MAX_STEPBACK || ungetCount > stepBackAmount) {
        throw std::invalid_argument("Step back exceeds allowed offset");
    }
    if (!currentBufferBlock) {
        throw std::runtime_error("Buffer doesn't have any content to step back.");
    }
    if (eofConsumed) {
    	eofConsumed = false;
    }
    stepBackAmount -= ungetCount;
    
    if (ungetCount <=  currentCharIndex) {
        currentCharIndex -= ungetCount;
    } else {
//        if (currentBufferBlock->getPrevious()) {
//
//        }
//        else {
//            throw std::runtime_error("Trying to access non-existent content.");
//        }
    	unsigned int diff = ungetCount - currentCharIndex;
		currentBufferBlock = currentBufferBlock->getPrevious();
		currentBlockIndex--;
		currentCharIndex = Buffer::BLOCK_SIZE - diff;
    }
        
}

unsigned int Buffer::getCurrentLine() {
	return currentBlockIndex;
}

unsigned int Buffer::getCurrentPos() {
	return currentCharIndex;
}

void Buffer::adjustIndiciesIn(int steps) {
	if (steps == 1) {
		if (currentCharIndex == Buffer::BLOCK_SIZE - 1) {
			currentCharIndex = 0;
			currentBlockIndex++;
		} else {
			currentCharIndex++;
		}
	} else if (steps < 0) {
		unsigned int steps_abs = (unsigned int)steps;
		if (steps_abs <= Buffer::MAX_STEPBACK) {
			if (currentCharIndex > steps_abs) {
				currentCharIndex-= steps_abs;
			} else {

				if (currentBlockIndex != 0) {
					currentCharIndex = Buffer::BLOCK_SIZE - (steps_abs - currentCharIndex);
					currentBlockIndex--;
				} else {
					currentCharIndex = 0;
				}

			}
		} else {
			throw std::invalid_argument("Offset can be either 1 or in range MAX_STEPBACK...0");
		}
	} else {
		throw std::invalid_argument("Offset can be either 1 or in range MAX_STEPBACK...0");
	}
}

bool Buffer::isEOF() {
	return eofConsumed;
}
