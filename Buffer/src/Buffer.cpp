#include "Buffer.h"

const unsigned int Buffer::BLOCK_SIZE = 256;
const unsigned int Buffer::MAX_STEPBACK = Buffer::BLOCK_SIZE / 2;


Buffer::Buffer(const char* filePath) {
    fileReader = new FileReader(filePath);
    currentBlockIndex = 0;
    currentCharIndex = 0;
    stepBackAmount = 0;
    currentBufferBlock = nullptr;
    eofConsumed = false;
    noFile = !fileReader->isOpen();
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

bool Buffer::isEOF() {
	return eofConsumed;
}

bool Buffer::isNoFile() {
	return noFile;
}

