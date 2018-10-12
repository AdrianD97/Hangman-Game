#include "Word.h"

Word::Word(sf::Font& font)
{
    this->font = sf::Font(font);
    this->wordText = sf::Text();
    this->letters = std::vector<bool>(26, false);
    this->map = std::unordered_map<char, std::vector<unsigned int>>();
    this->lines = std::string("");
}

Word::~Word()
{

}

void Word::load(std::string word)
{

    this->finish = word.size();
    unsigned int i, pos = 0;
    for (i = 0; i < this->finish; ++i) {
        if (i < this->finish - 1) {
            this->lines += "_ ";
        }
        this->letters[(int)word[i] - 97] = true;
        this->map[word[i]].push_back(pos);
        pos += 2;
    }
    this->lines += "_";

    this->wordText.setString(this->lines);
    this->wordText.setCharacterSize(50);
    this->wordText.setFont(this->font);
    this->wordText.setPosition(sf::Vector2f(350.0f, 200.0f));
}

void Word::free()
{
    for (unsigned int i = 0; i < 26; ++i) {
        this->letters[i] = false;
    }

    this->map.clear();

    this->lines = "";
}

bool Word::validateLetter(char letter)
{
    return this->letters[(int)letter - 97] == true;
}

void Word::change(char letter)
{
    this->letters[(int)letter - 97] = false;
    unsigned int size = this->map[letter].size();
    this->finish -= size;
    for (unsigned int i = 0; i < size; ++i) {
        this->lines[this->map[letter][i]] = letter;
    }

    this->wordText.setString(this->lines);
}

void Word::completeWord()
{
    unsigned int size;
    char letter;
    for (unsigned int i = 0; i < 26; ++i) {
        if (this->letters[i] == true) {
            letter = (char)(97 + i);
            size = this->map[letter].size();
            for (unsigned int j = 0; j < size; ++j) {
                this->lines[this->map[letter][j]] = letter;
            }
        }
    }

    this->wordText.setString(this->lines);
}

void Word::draw(sf::RenderWindow& window)
{
    window.draw(this->wordText);
}
