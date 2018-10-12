#include "Menu.h"

Menu::Menu(unsigned int nr_buttons, sf::Font& font, std::vector<std::string>& names, std::vector<sf::Vector2f>& positions)
{
    this->nr_buttons = nr_buttons;
    this->button_press = 0;
    this->items = std::vector<Button>();
    for (unsigned int  i = 0; i < nr_buttons; ++i) {
        this->items.push_back(Button(font, names[i], 30, sf::Color::Blue, positions[i]));
    }
}

Menu::~Menu()
{

}
