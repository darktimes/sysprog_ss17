#include "../includes/FileReader.h"

FileReader::FileReader(const char* filePath) {
    readFile = new ifstream(filePath);
    eof = false;
    currentCharIndex = 0;
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
        
    blockContent = new char[BufferConstants::BUFFER_BLOCK_SIZE];
    readFile->seekg (currentCharIndex);
    readFile->get(this->blockContent, BufferConstants::BUFFER_BLOCK_SIZE, '\0');

    currentCharIndex += strlen(blockContent);
    eof = readFile->eof();
    
    return blockContent;
}
 bool FileReader::isEof()
{
   return eof;
}

