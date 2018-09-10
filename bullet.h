#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

class bullet
{
public:
    bullet(sf::Texture *t, sf::Vector2f position,  
        sf::Vector2f direction, float initial_velocity,
        float max_velocity, float acceleration);
    virtual ~bullet();

    //accessors
    inline const sf::FloatRect get_global_bounds() const { return this->sprite_.getGlobalBounds();}
    inline const sf::Vector2f& get_position() const { return this->sprite_.getPosition(); }

    //functions
    void movement();
    void update();
    void draw(sf::RenderTarget &target);

private:
    sf::Vector2f current_velocity_;
    float max_velocity_;
    float acceleration_;
    sf::Vector2f direction_;
    sf::Texture *texture_;
    sf::Sprite sprite_;
    sf::Vector2f player_center_;
};

#endif // BULLET_H
