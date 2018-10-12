#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
    public:
        Button();
        Button(sf::Font& font, std::string text, unsigned int fontSize, sf::Color color, sf::Vector2f position);
        virtual ~Button();
        void draw(sf::RenderWindow& window);
        bool isHover(sf::Mouse& mouse, sf::RenderWindow& window);
        void setColor(sf::Color color);
        bool isClicked(sf::Event& evt);
        void setPosition(sf::Vector2f position);

    protected:

    private:
        sf::Text text;
};

#endif // BUTTON_H
