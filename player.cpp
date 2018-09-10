#include "player.h"

unsigned player::players = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };

player::player(sf::Texture *t, sf::Texture *bullet_t,
       int UP, int DOWN,
       int LEFT, int RIGHT,
       int SHOOT)

    : level_(1), exp_(0), exp_next_(100)
    , hp_(10), hp_next_(10), damage_(1)
    , damage_max_(2)
    , score_(0)
{
    this->texture_ = t;
    this->bullet_texture_ = bullet_t;
    this->sprite_.setTexture(*this->texture_);
    this->sprite_.setScale(0.13f, 0.13f);

    this->shooter_timer_max_ = 25;
    this->shooter_timer_ = this->shooter_timer_max_;
    this->damage_timer_max_ = 10;
    this->damage_timer_ = this->damage_timer_max_;

    this->controls[controls::UP] = UP;
    this->controls[controls::DOWN] = DOWN;
    this->controls[controls::LEFT] = LEFT;
    this->controls[controls::RIGHT] = RIGHT;
    this->controls[controls::SHOOT] = SHOOT;

    this->player_number = player::players;
    player::players++;

    std::cout << this->player_number << std::endl;
}

player::~player()
{

}

void player::movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::UP]))) {
        this->sprite_.move(0.f, -10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::DOWN]))) {
        this->sprite_.move(0.f, 10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::LEFT]))) {
        this->sprite_.move(-10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::RIGHT]))) {
        this->sprite_.move(10.f, 0.f);
    }
}

void player::combat() {
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key(this->controls[controls::SHOOT]))
            && this->shooter_timer_ >= shooter_timer_max_) {
        this->bullets_.push_back(
                bullet(bullet_texture_, this->player_center_, 
                    sf::Vector2f(1.f,0.f), 5.f, 35.f, 0.5f));

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
    
    this->player_center_.x = 
        this->sprite_.getPosition().x + this->sprite_.getGlobalBounds().width / 2;
    this->player_center_.y = 
        this->sprite_.getPosition().y + this->sprite_.getGlobalBounds().height / 2;

    this->movement();
    this->combat();
}

void player::draw(sf::RenderTarget &target)
{
    for (std::size_t i = 0; i < this->bullets_.size(); ++i) {
        this->bullets_[i].draw(target);
    }

    target.draw(this->sprite_);
}
