#include "bullet.h"

bullet::bullet(sf::Texture *t, sf::Vector2f position,  
        sf::Vector2f direction, float initial_velocity,
        float max_velocity, float acceleration)
{
    this->texture_ = t;
    this->sprite_.setTexture(*this->texture_);
    this->max_velocity_ = max_velocity;
    this->acceleration_ = acceleration;
    this->direction_ = direction;
    this->current_velocity_ = sf::Vector2f(
            initial_velocity * this->direction_.x, 
            initial_velocity * this->direction_.y);    
    
    this->sprite_.setScale(0.1f, 0.1f);
    this->sprite_.setPosition(sf::Vector2f(
                position.x - this->sprite_.getGlobalBounds().width / 2, 
                position.y - this->sprite_.getGlobalBounds().height / 2));
}

bullet::~bullet()
{

}

void bullet::movement()
{
    if(this->acceleration_ > 0.f) {
        if(this->current_velocity_.x < this->max_velocity_)
        this->current_velocity_.x += this->acceleration_ * this->direction_.x;
        
        if(this->current_velocity_.y < this->max_velocity_)
        this->current_velocity_.x += this->acceleration_ * this->direction_.y;
    }
    else {
        this->current_velocity_ = sf::Vector2f(
                this->max_velocity_ * this->direction_.x, 
                this->max_velocity_ * this->direction_.y);
    }
    this->sprite_.move(this->current_velocity_);    
}

void bullet::update()
{
    this->movement();
}

void bullet::draw(sf::RenderTarget &target)
{
    target.draw(this->sprite_);
}
