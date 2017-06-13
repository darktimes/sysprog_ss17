#include "FileReader.h"

FileReader::FileReader(const char* filePath) {
    readFile = new std::ifstream(filePath);
    eof = false;
    currentCharIndex = 0;
    blockContent = nullptr;
}

FileReader::~FileReader() {
    readFile->close();
}
char* FileReader::getNextFileBlock()
{
    if (!readFile->is_open())
        throw std::runtime_error("File is not opened!");
        
    if (eof)
        throw std::runtime_error("Eof reached, no next file block!");
        
    blockContent = new char[Buffer::BUFFER_BLOCK_SIZE];
    readFile->seekg (currentCharIndex);
    readFile->get(this->blockContent, Buffer::BUFFER_BLOCK_SIZE, '\0');

    currentCharIndex += strlen(blockContent);
    eof = readFile->eof();
    
    return blockContent;
}
 bool FileReader::isEof()
{
   return eof;
}

