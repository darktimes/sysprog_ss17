#include "FileReader.h"

FileReader::FileReader(const char* filePath) {
    readFile = new std::ifstream(filePath);
}

FileReader::~FileReader() {
    readFile->close();
}
BufferBlock* FileReader::getBufferBlockAt(unsigned int blockIndex)
{
    if (!readFile->is_open())
        throw std::runtime_error("Couldn't open the file.");
        
        
    char* blockContent = new char[Buffer::BLOCK_SIZE];
    readFile->seekg(blockIndex * Buffer::BLOCK_SIZE);
    readFile->get(blockContent, Buffer::BLOCK_SIZE + 2, '\0');
    unsigned int length = readFile->gcount();
    if (length == 0) {
    	return nullptr;
    } else {
    	length -= 1;
    }
    return new BufferBlock(blockContent, length);
}


