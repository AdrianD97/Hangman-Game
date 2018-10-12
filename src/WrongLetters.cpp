#include "WrongLetters.h"

WrongLetters::WrongLetters(sf::Font& font)
{
    this->attempt_message = sf::Text("You have 11 attempts.", font, 25);
    this->attempt_message.setPosition(sf::Vector2f(400.0f, 100.0f));
    this->attempt_message.setFillColor(sf::Color::Magenta);
    this->message = sf::Text("Wrong letters:", font, 30);
    this->message.setPosition(sf::Vector2f(350.0f, 300.0f));
    this->message.setFillColor(sf::Color::Red);
    this->letters = sf::Text("", font, 40);
    this->letters.setPosition(sf::Vector2f(350.0f, 350.0f));
    this->letters.setFillColor(sf::Color::Red);
}

WrongLetters::~WrongLetters()
{

}

void WrongLetters::setWrongLetters(char letter)
{
    std::string content = this->letters.getString();
    content.push_back(letter);
    content.push_back(' ');
    this->letters.setString(content);
}

void WrongLetters::setAttemptMessage(std::string message)
{
    this->attempt_message.setString(message);
}

void WrongLetters::draw(sf::RenderWindow& window)
{
    window.draw(this->attempt_message);
    window.draw(this->message);
    window.draw(this->letters);
}

void WrongLetters::reset()
{
    this->letters.setString("");
}
