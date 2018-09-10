#ifndef GAME_H
#define GAME_H

#include "player.h"

class game
{
public:
    game(sf::RenderWindow*);
    virtual ~game();

    //accessors
    inline sf::RenderWindow& getWindow() { return *this->window_; }

    //setters

    //functions
    void init_texts();
    void init_UI();
    void UIupdate();
    void update();
    void drawUI();
    void draw();

private:
    sf::RenderWindow* window_;

    //text
    sf::Font font_;
    std::vector<sf::Text> follow_player_texts;
    std::vector<sf::Text> static_player_texts;

    //players
    std::vector<player> players_;

    //textures
    sf::Texture player_texture_;
    sf::Texture bullet_texture_;
};

#endif // GAME_H
