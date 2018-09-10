#include "bullet.h"

bullet::bullet(sf::Texture *t, sf::Vector2f position
               , sf::Vector2f max_velocity)
{
    this->texture_ = t;
    this->sprite_.setTexture(*this->texture_);
    this->max_velocity_ = max_velocity;

    this->sprite_.setScale(0.1f, 0.1f);
    this->sprite_.setPosition(position);
}

bullet::~bullet()
{

}

void bullet::movement()
{
    this->sprite_.move(this->max_velocity_.x, this->max_velocity_.y);
}

void bullet::update()
{
    this->movement();
}

void bullet::draw(sf::RenderTarget &target)
{
    target.draw(this->sprite_);
}
