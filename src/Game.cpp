#include "Game.h"

Game::Game()
{
    this->window = 1;
    this->table = new sf::RenderWindow(sf::VideoMode(800, 600), "Hangman", sf::Style::Close | sf::Style::Titlebar);
    this->background = new sf::RectangleShape(sf::Vector2f(800.0f, 600.0f));
}

Game::~Game()
{
    delete this->background;
    delete this->table;
}

void Game::run(sf::Texture* texture)
{
    bool gameOver = false;
    bool win_game = false;
    bool lost_game = false;
    unsigned int attempts = 11;
    unsigned int nr_texture = 2;
    char letter;
    unsigned int number;
    std::string path_to_file = std::string();
    std::string path_to_textures = std::string("Images/Hangman/image");
    float time = float(0.0f);
    unsigned int score = 0;

    //create a music object
    sf::Music music;
    if (!music.openFromFile("Music/sound.ogg")) {
        exit(EXIT_FAILURE);
    }
    music.setLoop(true);
    music.play();

    //create a image object
    sf::Image image = sf::Image();
    if (!image.loadFromFile("Images/icon.jpg")) {
        exit(EXIT_FAILURE);
    }
    sf::Vector2u imageSize = image.getSize();
    //set Window icon
    this->table->setIcon(imageSize.x, imageSize.y, image.getPixelsPtr());

    //set table texture
    this->background->setTexture(texture);

    //create a loader object and load a font
    Loader<sf::Font> loaderFont = Loader<sf::Font>("Fonts/ItalicFont.ttf");
    sf::Font font = loaderFont.load();
    //create a button object
    Button startGame(font, "Start Game", 50, sf::Color::Red, sf::Vector2f(400.0f, 430.0f));

    //create a mosue object
    sf::Mouse mouse;

    //create a loader object and load a texture for window2
    Loader<sf::Texture> loaderTexture = Loader<sf::Texture>();

    //create a Reader object
    Reader reader = Reader();

    //create a Word object
    Word guessWord = Word(font);

    //create a WrongLetters object
    WrongLetters wrong_letters = WrongLetters(font);

    //create a Text message
    sf::Text result = sf::Text("", font, 100);

    //create a clock
    sf::Clock clock = sf::Clock();

    //create some buttons;
    Button newGame = Button(font, "New Game", 40, sf::Color::Black, sf::Vector2f(0.0f, 0.0f));
    Button nextGame = Button(font, "Next Game", 40, sf::Color::Black, sf::Vector2f(0.0f, 0.0f));
    Button backToMenu = Button(font, "Back to menu", 40, sf::Color::Black, sf::Vector2f(0.0f, 0.0f));
    Button exit = Button(font, "Quit", 40, sf::Color::Black, sf::Vector2f(0.0f, 0.0f));

    //create options
    std::vector<std::string> options = std::vector<std::string>();
    options.push_back("Fruits");
    options.push_back("Animals");
    options.push_back("Footbal Teams");
    options.push_back("States");
    options.push_back("Capitals");

    std::vector<sf::Vector2f> options_position = std::vector<sf::Vector2f>();
    options_position.push_back(sf::Vector2f(600.0f, 250.0f));
    options_position.push_back(sf::Vector2f(600.0f, 300.0f));
    options_position.push_back(sf::Vector2f(600.0f, 350.0f));
    options_position.push_back(sf::Vector2f(600.0f, 400.0f));
    options_position.push_back(sf::Vector2f(600.0f, 450.0f));

    //load a font for menu
    loaderFont.setPath("Fonts/OpenSans-Bold.ttf");
    sf::Font fontMenu = loaderFont.load();
    //create a menu object
    Menu menu = Menu(5, fontMenu, options, options_position);

    //create a text message for sound
    sf::Text want_sound = sf::Text("Sound", fontMenu);
    want_sound.setPosition(sf::Vector2f(100.0f, 100.0f));
    want_sound.setFillColor(sf::Color::Green);

    //create a rectangleShape object for sound options
    sf::RectangleShape soundOptions = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
    soundOptions.setPosition(sf::Vector2f(115.0f, 140.0f));
    loaderTexture.setPath("Images/sound.jpg");
    sf::Texture soundTexture = loaderTexture.load();
    sf::Vector2u soundTextureSize = soundTexture.getSize();
    soundOptions.setTexture(&soundTexture);
    soundOptions.setTextureRect(sf::IntRect(0, 0, soundTextureSize.x, soundTextureSize.y / 2));
    unsigned int soundOptionChooseen = 1;

    //create a timed message
    sf::Text timed = sf::Text("Timed", fontMenu);
    timed.setPosition(sf::Vector2f(600.0f, 100.0f));
    timed.setFillColor(sf::Color::Green);

    //create a rectangleShape object for timed options
    sf::RectangleShape timedOptions = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
    timedOptions.setPosition(sf::Vector2f(620.0f, 140.0f));
    loaderTexture.setPath("Images/no.jpg");
    sf::Texture timedTexture = loaderTexture.load();
    timedOptions.setTexture(&timedTexture);
    unsigned int timedOptionChooseen = 1;

    //create a score message
    sf::Text score_message = sf::Text("Score: 0", fontMenu);
    score_message.setPosition(sf::Vector2f(350.0f, 450.0f));
    score_message.setFillColor(sf::Color::Black);

    //create a sf::Text message
    sf::Text time_left = sf::Text("Time left: 15", fontMenu);
    time_left.setPosition(sf::Vector2f(350.0f, 520.0f));
    time_left.setFillColor(sf::Color::Black);

    while(this->table->isOpen()) {
        sf::Event evt;

        while(this->table->pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                this->table->close();
            }

            if (this->window == 1) {
                if (startGame.isHover(mouse, *this->table)) {
                    startGame.setColor(sf::Color::Green);
                    if (startGame.isClicked(evt)) {
                        loaderTexture.setPath("Images/background1.jpg");
                        *texture = loaderTexture.load();
                        this->window = 2;
                    }
                } else {
                    startGame.setColor(sf::Color::Red);
                }

                if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left &&
                    soundOptions.getGlobalBounds().contains(float(mouse.getPosition(*this->table).x), float(mouse.getPosition(*this->table).y))) {
                    if (soundOptionChooseen == 1) {
                        soundOptionChooseen = 2;
                        music.stop();
                        soundOptions.setTextureRect(sf::IntRect(0, soundTextureSize.y / 2, soundTextureSize.x, soundTextureSize.y / 2));
                    } else {
                        soundOptionChooseen = 1;
                        music.play();
                        soundOptions.setTextureRect(sf::IntRect(0, 0, soundTextureSize.x, soundTextureSize.y / 2));
                    }
                }

                if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left &&
                    timedOptions.getGlobalBounds().contains(float(mouse.getPosition(*this->table).x), float(mouse.getPosition(*this->table).y))) {
                    if (timedOptionChooseen == 1) {
                        timedOptionChooseen = 2;
                        loaderTexture.setPath("Images/yes.jpg");
                        timedTexture = loaderTexture.load();
                    } else {
                        timedOptionChooseen = 1;
                        loaderTexture.setPath("Images/no.jpg");
                        timedTexture = loaderTexture.load();
                    }
                }
            } else {
                if (this->window == 2) {
                    for (unsigned int i = 0; i < menu.nr_buttons; ++i) {
                        if (menu.items[i].isHover(mouse, *this->table)) {
                            menu.items[i].setColor(sf::Color::Green);
                            if (menu.items[i].isClicked(evt)) {
                                this->window = 3;
                                menu.button_press = i + 1;
                                nr_texture = 2;
                                loaderTexture.setPath("Images/Hangman/image1.jpg");
                                *texture = loaderTexture.load();
                            }
                        } else {
                            menu.items[i].setColor(sf::Color::Blue);
                        }
                    }

                    if (menu.button_press != 0) {
                        switch (menu.button_press) {
                            case 1 :
                                path_to_file = "Files/fruits.txt";
                                break;
                            case 2:
                                path_to_file = "Files/animals.txt";
                                break;
                            case 3:
                                path_to_file = "Files/teams.txt";
                                break;
                            case 4:
                                path_to_file = "Files/states.txt";
                                break;
                            case 5:
                                path_to_file = "Files/capitals.txt";
                                break;
                        }

                        reader.setPath(path_to_file);
                        reader.read();
                        //create a generator object
                        Generator generator = Generator(reader.size);
                        number = generator.getRandomNumber();
                        //obtain a random word from a specific list
                        guessWord.load(reader.getWord(number));

                        clock.restart();
                    }
                } else {
                    if (this->window == 3) {
                        if (evt.type == sf::Event::TextEntered) {
                            if ((evt.text.unicode >= 97 && evt.text.unicode <= 122) || (evt.text.unicode >= 65 && evt.text.unicode <= 90)) {
                                letter = tolower(static_cast<char>(evt.text.unicode));
                                if (guessWord.validateLetter(letter)) {
                                    guessWord.change(letter);
                                    if (guessWord.finish == 0) {
                                        this->window = 4;
                                        gameOver = true;
                                        clock.restart();
                                        result.setString("Winner");
                                        result.setPosition(sf::Vector2f(240.0f, 120.0f));
                                        win_game = true;
                                        ++score;
                                        newGame.setPosition(sf::Vector2f(400.0f, 300.0f));
                                        nextGame.setPosition(sf::Vector2f(400.0f, 350.0f));
                                        backToMenu.setPosition(sf::Vector2f(400.0f, 400.0f));
                                        exit.setPosition(sf::Vector2f(400.0f, 450.0f));
                                    }
                                } else {
                                    --attempts;
                                    wrong_letters.setWrongLetters(letter);
                                    std::stringstream ss1 = std::stringstream();
                                    ss1 << nr_texture;
                                    loaderTexture.setPath(path_to_textures + ss1.str() + ".jpg");
                                    *texture = loaderTexture.load();

                                    if (attempts > 0) {
                                        std::stringstream ss2 = std::stringstream();
                                        ss2 << attempts;
                                        wrong_letters.setAttemptMessage("You have " + ss2.str() + " attempts.");
                                        ++nr_texture;
                                    } else {
                                        lost_game = true;
                                    }
                                }
                            }
                        }
                    } else {
                        if (this->window == 4) {
                            if (gameOver == false) {
                                if (newGame.isHover(mouse, *this->table)) {
                                    newGame.setColor(sf::Color::Green);
                                    if (newGame.isClicked(evt)) {
                                        loaderTexture.setPath("Images/background2.jpg");
                                        *texture = loaderTexture.load();
                                        this->window = 1;
                                        menu.button_press = 0;
                                        attempts = 11;
                                        win_game = false;
                                        guessWord.free();
                                        reader.free();
                                        wrong_letters.reset();
                                        wrong_letters.setAttemptMessage("You have 11 attempts.");
                                        score_message.setString("Score: 0");
                                        score = 0;
                                    }
                                } else {
                                    newGame.setColor(sf::Color::Black);
                                }

                                if (backToMenu.isHover(mouse, *this->table)) {
                                    backToMenu.setColor(sf::Color::Green);
                                    if (backToMenu.isClicked(evt)) {
                                        loaderTexture.setPath("Images/background1.jpg");
                                        *texture = loaderTexture.load();
                                        this->window = 2;
                                        menu.button_press = 0;
                                        attempts = 11;
                                        win_game = false;
                                        guessWord.free();
                                        reader.free();
                                        wrong_letters.reset();
                                        wrong_letters.setAttemptMessage("You have 11 attempts.");
                                        score_message.setString("Score: 0");
                                        score = 0;
                                    }
                                } else {
                                    backToMenu.setColor(sf::Color::Black);
                                }

                                if (exit.isHover(mouse, *this->table)) {
                                    exit.setColor(sf::Color::Green);
                                    if (exit.isClicked(evt)) {
                                        this->table->close();
                                    }
                                } else {
                                    exit.setColor(sf::Color::Black);
                                }

                                if (win_game == true) {
                                    if (nextGame.isHover(mouse, *this->table)) {
                                        nextGame.setColor(sf::Color::Green);
                                        if (nextGame.isClicked(evt)) {
                                            loaderTexture.setPath("Images/Hangman/image1.jpg");
                                            *texture = loaderTexture.load();
                                            this->window = 3;
                                            menu.button_press = 0;
                                            attempts = 11;
                                            win_game = false;
                                            guessWord.free();
                                            wrong_letters.reset();
                                            wrong_letters.setAttemptMessage("You have 11 attempts.");
                                            Generator generator = Generator(reader.size);
                                            number = generator.getRandomNumber();
                                            guessWord.load(reader.getWord(number));
                                            nr_texture = 2;
                                            std::stringstream ss = std::stringstream();
                                            ss << score;
                                            score_message.setString("Score: " + ss.str());
                                            clock.restart();
                                        }
                                    } else {
                                        nextGame.setColor(sf::Color::Black);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (this->window == 3) {
            time = clock.getElapsedTime().asSeconds();
            if ((timedOptionChooseen == 2 && time >= 15) || lost_game == true) {
                lost_game = false;
                time = 0;
                std::stringstream ss2 = std::stringstream();
                ss2 << 0;
                wrong_letters.setAttemptMessage("You have " + ss2.str() + " attempts.");
                gameOver = true;
                this->window = 4;
                guessWord.completeWord();
                clock.restart();
                result.setString("Game Over");
                result.setPosition(sf::Vector2f(150.0f, 120.0f));
                newGame.setPosition(sf::Vector2f(400.0f, 300.0f));
                backToMenu.setPosition(sf::Vector2f(400.0f, 350.0f));
                exit.setPosition(sf::Vector2f(400.0f, 400.0f));
            } else {
                std::stringstream ss3 = std::stringstream();
                ss3 << (int)(15 - time);
                time_left.setString("Time left: " + ss3.str());
            }
        }
        else {
            if (this->window == 4) {
                if (gameOver == true) {
                    time = clock.getElapsedTime().asSeconds();
                    if (time > 1.5) {
                        time = 0.0f;
                        gameOver = false;
                        loaderTexture.setPath("Images/image4.jpg");
                        *texture = loaderTexture.load();
                    }
                }
            }
        }

        this->table->clear(sf::Color::White);
        this->table->draw(*this->background);
        if (this->window == 1) {
            startGame.draw(*this->table);
            this->table->draw(want_sound);
            this->table->draw(soundOptions);
            this->table->draw(timed);
            this->table->draw(timedOptions);
        } else {
            if (this->window == 2) {
                for (unsigned int i = 0; i < menu.nr_buttons; ++i) {
                    menu.items[i].draw(*this->table);
                }
            } else {
                if (this->window == 3) {
                    if (gameOver == false) {
                        guessWord.draw(*this->table);
                        wrong_letters.draw(*this->table);
                        this->table->draw(score_message);
                        if (timedOptionChooseen == 2) {
                            this->table->draw(time_left);
                        }
                    }
                } else {
                    if (this->window == 4) {
                        if (gameOver == true) {
                            guessWord.draw(*this->table);
                            wrong_letters.draw(*this->table);
                            this->table->draw(score_message);
                            if (timedOptionChooseen == 2) {
                                this->table->draw(time_left);
                            }
                        } else {
                            result.setFillColor(sf::Color::Magenta);
                            this->table->draw(result);
                            newGame.draw(*this->table);
                            backToMenu.draw(*this->table);
                            exit.draw(*this->table);
                            if (win_game == true) {
                                nextGame.draw(*this->table);
                            }
                        }
                    }
                }
            }
        }
        this->table->display();
    }
}
