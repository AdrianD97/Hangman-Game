#ifndef LOADER_H
#define LOADER_H

#include <string>

template <class T> class Loader
{
    public:
        Loader();
        Loader(std::string path);
        virtual ~Loader();
        T load();
        void setPath(std::string path);

    protected:

    private:
        std::string path;
};

#endif // LOADER_H
