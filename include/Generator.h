#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>

class Generator
{
    public:
        Generator(unsigned int limit);
        virtual ~Generator();
        unsigned int getRandomNumber();

    protected:

    private:
        unsigned int limit;
};

#endif // GENERATOR_H
