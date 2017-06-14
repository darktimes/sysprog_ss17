#include "BufferBlock.h"

BufferBlock::BufferBlock(char* content,unsigned int length)
{
    this->content = content;
    this->length = length;
    previous = nullptr;
    next = nullptr;
}

BufferBlock::~BufferBlock() 
{
	delete[] content;
}

char BufferBlock::getCharAt(unsigned int index) const
{
	if (index < length) {
		return content[index];
	} else if(isLastBlock()) {
		return '\0';
	} else {
		throw std::range_error("Index exceeds length.");
	}
}
unsigned int BufferBlock::getLength() const
{
    return this->length;
}
void BufferBlock::setNext(BufferBlock* bufferBlock)
{
    this->next = bufferBlock;
    bufferBlock->previous = this;
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

bool BufferBlock::isLastBlock() const{
	return length != Buffer::BLOCK_SIZE;
}






