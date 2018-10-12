#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Menu
{
    public:
        Menu(unsigned int nr_buttons, sf::Font& font, std::vector<std::string>& names, std::vector<sf::Vector2f>& positions);
        virtual ~Menu();

    public:
        std::vector<Button> items;
        unsigned int button_press;
        unsigned int nr_buttons;

    protected:

    private:
};

#endif // MENU_H
