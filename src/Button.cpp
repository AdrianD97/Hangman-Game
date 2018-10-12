#include "Button.h"

Button::Button()
{
    this->text = sf::Text();
}

Button::Button(sf::Font& font, std::string text, unsigned int fontSize, sf::Color color, sf::Vector2f position)
{
    this->text = sf::Text();
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(color);
    this->text.setPosition(position);
    float width = float(this->text.getLocalBounds().width / 2);
    float height = float(this->text.getLocalBounds().height / 2);
    this->text.setOrigin(sf::Vector2f(width, height));
}

Button::~Button()
{

}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(this->text);
}

bool Button::isHover(sf::Mouse& mouse, sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = mouse.getPosition(window);
    return this->text.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y));
}

void Button::setColor(sf::Color color)
{
    this->text.setFillColor(color);
}

bool Button::isClicked(sf::Event& evt)
{
    return (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left);
}

void Button::setPosition(sf::Vector2f position)
{
    this->text.setPosition(position);
}
