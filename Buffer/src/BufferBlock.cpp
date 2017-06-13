#include "BufferBlock.h"

BufferBlock::BufferBlock(char* content) 
{
    this->content = content;
    this->length = strlen(content);
    previous = nullptr;
    next = nullptr;
}

BufferBlock::~BufferBlock() 
{
	delete[] content;
}

char BufferBlock::getCharAt(unsigned int index) const
{
    if (length <= index)
        return '\0';
    else
        return content[index];
}
unsigned int BufferBlock::getLength() const
{
    return this->length;
}
void BufferBlock::setNext(BufferBlock* bufferBlock)
{
    this->next = bufferBlock;
    this->previous = bufferBlock->previous;
 //   bufferBlock->previous = this;
}
void BufferBlock::clearPrevious()
{
    delete this->previous;
    this->previous = nullptr;
}
BufferBlock* BufferBlock::getNext()
{
    return next;
}
BufferBlock* BufferBlock::getPrevious()
{
    return previous;
}








