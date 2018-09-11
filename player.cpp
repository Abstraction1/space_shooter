#include "player.h"

unsigned player::players = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };

player::player(sf::Texture *t, sf::Texture *bullet_t, sf::Texture *main_gun_texture, int UP, int DOWN, int LEFT, int RIGHT, int SHOOT)
    : level_(1), exp_(0), exp_next_(100), hp_(10), hp_next_(10), damage_(1), damage_max_(2), score_(0)
{
    this->texture_ = t;
    this->bullet_texture_ = bullet_t;
    this->sprite_.setTexture(*this->texture_);
    this->sprite_.setScale(0.13f, 0.13f);

    this->main_gun_texture_ = main_gun_texture;
    this->main_gun_sprite_.setTexture(*this->main_gun_texture_);

    this->shooter_timer_max_ = 25;
    this->shooter_timer_ = this->shooter_timer_max_;
    this->damage_timer_max_ = 10;
    this->damage_timer_ = this->damage_timer_max_;

    this->controls[controls::UP] = UP;
    this->controls[controls::DOWN] = DOWN;
    this->controls[controls::LEFT] = LEFT;
    this->controls[controls::RIGHT] = RIGHT;
    this->controls[controls::SHOOT] = SHOOT;
    
    this->max_velocity_ = 25.f;
    this->acceleration_ = 0.8f;
    this->stabilizer_force_ = 0.4f; 

    this->player_number = player::players;
    player::players++;
}

player::~player()
{

}

void player::update_accessories()
{
    this->main_gun_sprite_.setPosition(
            this->player_center_.x - this->main_gun_sprite_.getGlobalBounds().width,
            this->player_center_.y - this->main_gun_sprite_.getGlobalBounds().height); 
}

void player::movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::UP]))) {
       this->direction_.x = 0.f; 
       this->direction_.y = -1.f; 

       if(this->current_velocity_.y > -this->max_velocity_ && direction_.y < 0)
          this->current_velocity_.y += this->direction_.y * this->acceleration_;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::DOWN]))) { 
       this->direction_.x = 0.f; 
       this->direction_.y = 1.f; 

       if(this->current_velocity_.y < this->max_velocity_ && direction_.y > 0)
          this->current_velocity_.y += this->direction_.y * this->acceleration_;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::LEFT]))) {
       this->direction_.x = -1.f; 
       this->direction_.y = 0.f; 

       if(this->current_velocity_.x > -this->max_velocity_ && direction_.x < 0)
          this->current_velocity_.x += this->direction_.x * this->acceleration_;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::RIGHT]))) {
       this->direction_.x = 1.f; 
       this->direction_.y = 0.f; 

       if(this->current_velocity_.x < this->max_velocity_ && direction_.x > 0)
          this->current_velocity_.x += this->direction_.x * this->acceleration_;
    }
    
    // DRAG FORE
    
    if(this->current_velocity_.x > 0) {
        this->current_velocity_.x -= this->stabilizer_force_;
        if(this->current_velocity_.x < 0) {
            this->current_velocity_.x = 0;
        }
    }
    else if(this->current_velocity_.x < 0) {
        this->current_velocity_.x += this->stabilizer_force_;
        if(this->current_velocity_.x > 0) {
            this->current_velocity_.x = 0;
        }
    }
    if(this->current_velocity_.y > 0) {
        this->current_velocity_.y -= this->stabilizer_force_;
        if(this->current_velocity_.y < 0) {
            this->current_velocity_.y = 0;
        }
    }
    else if(this->current_velocity_.y < 0) {
        this->current_velocity_.y += this->stabilizer_force_;
        if(this->current_velocity_.y > 0) {
            this->current_velocity_.y = 0;
        }
    }

    //final move
    this->sprite_.move(this->current_velocity_.x, this->current_velocity_.y);
}

void player::combat() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::SHOOT])) && this->shooter_timer_ >= shooter_timer_max_) {
        this->bullets_.push_back(bullet(bullet_texture_, this->player_center_, sf::Vector2f(1.f,0.f), 2.f, 50.f, 1.f));
        this->shooter_timer_ = 0; // reset timer
    }
}

void player::update(sf::Vector2u window_bounds)
{
    //update timers
    if (this->shooter_timer_ < this->shooter_timer_max_) {
        this->shooter_timer_++;
    }

    if (this->damage_timer_ < this->damage_timer_max_) {
        this->damage_timer_++;
    }
    
    //update position
    this->player_center_.x = this->sprite_.getPosition().x + this->sprite_.getGlobalBounds().width / 2;
    this->player_center_.y = this->sprite_.getPosition().y + this->sprite_.getGlobalBounds().height / 2;

    this->movement();
    this->combat();
}

void player::draw(sf::RenderTarget &target)
{
    for (std::size_t i = 0; i < this->bullets_.size(); ++i) {
        this->bullets_[i].draw(target);
    }

    target.draw(this->main_gun_sprite_);
    target.draw(this->sprite_);

}
