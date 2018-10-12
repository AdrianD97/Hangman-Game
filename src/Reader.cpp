#include "Reader.h"

Reader::Reader()
{
    this->words = std::vector<std::string>();
    this->size = 0;
}

Reader::~Reader()
{

}

void Reader::setPath(std::string path)
{
    this->path = path;
}

void Reader::read()
{
    std::string word;
    std::ifstream file = std::ifstream(this->path);

    while (std::getline(file, word)) {
        this->words.push_back(word);
        ++this->size;
    }
    file.close();
}

std::string Reader::getWord(unsigned int index)
{
    return this->words[index];
}

void Reader::free()
{
    this->words.clear();
    this->size = 0;
}

/*unsigned int Reader::getSize()
{

    return this->words.size();
}*/
