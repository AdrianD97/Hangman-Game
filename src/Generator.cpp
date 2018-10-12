#include "Generator.h"

Generator::Generator(unsigned int limit)
{
    this->limit = limit;
}

Generator::~Generator()
{

}

unsigned int Generator::getRandomNumber()
{
    return rand() % limit;
}
