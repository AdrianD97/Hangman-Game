#include "Loader.h"
#include <SFML/Graphics.hpp>

template <class T> Loader<T>::Loader(std::string path)
{
    this->path = std::string(path);
}

template <class T> Loader<T>::Loader()
{

}

template <class T> Loader<T>::~Loader()
{

}

template <class T> T Loader<T>::load()
{
    T item = T();
    if (!item.loadFromFile(this->path))
    {
        exit(EXIT_FAILURE);
    }

    return item;
}

template <class T> void Loader<T>::setPath(std::string path)
{
    this->path = path;
}

template class Loader<sf::Texture>;
template class Loader<sf::Font>;
