#ifndef READER_H
#define READER_H

#include <string>
#include <vector>
#include <fstream>

class Reader
{
    public:
        Reader();
        virtual ~Reader();
        void setPath(std::string path);
        void read();
        std::string getWord(unsigned int index);
        void free();

        //unsigned int getSize();

    public:
        unsigned int size;

    protected:

    private:
        std::string path;
        std::vector<std::string> words;
};

#endif // READER_H
