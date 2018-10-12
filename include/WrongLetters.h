#ifndef WRONGLETTERS_H
#define WRONGLETTERS_H

#include <SFML/Graphics.hpp>
#include <string>

class WrongLetters
{
    public:
        WrongLetters(sf::Font& font);
        virtual ~WrongLetters();
        void draw(sf::RenderWindow& window);
        void setWrongLetters(char letter);
        void setAttemptMessage(std::string message);
        void reset();

    protected:

    private:
        sf::Text message;
        sf::Text letters;
        sf::Text attempt_message;
};

#endif // WRONGLETTERS_H
