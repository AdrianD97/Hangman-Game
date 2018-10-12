#ifndef WORD_H
#define WORD_H

#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>
#include<vector>

class Word
{
    public:
        Word(sf::Font& font);
        virtual ~Word();
        void load(std::string word);
        void draw(sf::RenderWindow& window);
        void free();
        bool validateLetter(char letter);
        void change(char letter);
        void completeWord();

    public:
        unsigned int finish;

    protected:

    private:
        sf::Font font;
        sf::Text wordText;
        std::vector<bool> letters;
        std::unordered_map<char, std::vector<unsigned int>> map;
        std::string lines;
};

#endif // WORD_H
