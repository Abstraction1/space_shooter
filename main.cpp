#include "game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1440, 990), "Game", sf::Style::Default);

    game g(&window);

    // game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        g.update();
        g.draw();
    }
    return 0;
}
