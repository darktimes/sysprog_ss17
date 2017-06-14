#pragma once

#include "Buffer.h"

class BufferBlock {
public:
	BufferBlock(char*, unsigned int);
	virtual ~BufferBlock();
    char getCharAt(unsigned int) const;
    unsigned int getLength() const;
    void setNext(BufferBlock*);
    void clearPrevious();
    BufferBlock* getNext();
    BufferBlock* getPrevious();
    bool isLastBlock() const;

private:
    char* content;
    unsigned int length;
    BufferBlock* next;
    BufferBlock* previous;
};
