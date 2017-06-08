#include "../includes/FileReader.h"


FileReader::FileReader(const char* filePath) {
    this->filePath = filePath;
    this->readFile->open(filePath);
    this->currentIndex = 0;
}

FileReader::~FileReader() {
    //TODO: close reader
    this->readFile->close();
}
char* FileReader::getNextBlock()
{
    delete[] blockContent;
    blockContent = new char[BufferConstants::BUFFER_BLOCK_SIZE];
    readFile->seekg (currentIndex);
    readFile->read (this->blockContent, BufferConstants::BUFFER_BLOCK_SIZE);
    
    currentIndex += BufferConstants::BUFFER_BLOCK_SIZE;
    return blockContent;
}

