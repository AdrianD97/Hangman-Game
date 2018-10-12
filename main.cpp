#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include "Game.h"
#include "Loader.h"

int main()
{
    srand((unsigned)time(0));
    Loader<sf::Texture> loader = Loader<sf::Texture>("Images/background2.jpg");
    sf::Texture* texture = new sf::Texture(loader.load());
    Game* hanging = new Game();
    hanging->run(texture);

    delete texture;
    delete hanging;
    return 0;
}
