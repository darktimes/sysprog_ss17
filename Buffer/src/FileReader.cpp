#include "FileReader.h"

FileReader::FileReader(const char* filePath) {
    readFile = new std::ifstream(filePath);
    strBuffer = readFile->rdbuf();
    opened = readFile->is_open();
}

FileReader::~FileReader() {
    readFile->close();
}
BufferBlock* FileReader::getBufferBlockAt(unsigned int blockIndex)
{
    if (!opened) {
        throw std::runtime_error("Couldn't open the file.");
    }
        
    char* blockContent = new char[Buffer::BLOCK_SIZE];
    strBuffer->pubseekpos(blockIndex * Buffer::BLOCK_SIZE);
    std::streamsize length = strBuffer->sgetn(blockContent, Buffer::BLOCK_SIZE);
    return new BufferBlock(blockContent, length);
}

bool FileReader::isOpen() {
	return opened;
}


