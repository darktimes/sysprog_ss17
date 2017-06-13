#pragma once
#include "LibConstants.h"
#include <string.h>

class BufferBlock {
public:
	BufferBlock(char*);
	virtual ~BufferBlock();
    char getCharAt(unsigned int) const;
    unsigned int getLength() const;
    void setNext(BufferBlock*);
    void clearPrevious();
    BufferBlock* getNext();
    BufferBlock* getPrevious();

private:
    char* content;
    unsigned int length;
    BufferBlock* next;
    BufferBlock* previous;
};
