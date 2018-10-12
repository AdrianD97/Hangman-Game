#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <sstream>
#include <string>
#include "Loader.h"
#include "Button.h"
#include "Menu.h"
#include "Reader.h"
#include "Word.h"
#include "Generator.h"
#include "WrongLetters.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void run(sf::Texture* texture);

    private:
        unsigned int window;
        sf::RenderWindow* table;
        sf::RectangleShape* background;
};

#endif // GAME_H
