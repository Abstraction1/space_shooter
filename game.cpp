#include "game.h"

game::game(sf::RenderWindow *window)
{
    this->window_ = window;
    this->window_->setFramerateLimit(60);

    //init fonts
    this->font_.loadFromFile("/home/chains/space_shooter/Fonts/Dosis-Light.ttf");

    //init texture
    this->player_texture_.loadFromFile("/home/chains/space_shooter/Textures/ship.png");
    this->bullet_texture_.loadFromFile("/home/chains/space_shooter/Textures/missileTex01.png");

    //init player
    this->players_.push_back(player(&player_texture_, &bullet_texture_));

//    this->players_.push_back(player(&player_texture_, &bullet_texture_
//                                    , sf::Keyboard::I, sf::Keyboard::K
//                                    , sf::Keyboard::L, sf::Keyboard::RShift));

    this->init_UI();
}

game::~game()
{

}

void game::init_texts()
{

}

void game::init_UI()
{
    for (std::size_t i = 0; i < this->players_.size(); ++i) {
        sf::Text temp_text;
    }
}

void game::UIupdate()
{
    for (std::size_t i = 0; i < this->follow_player_texts.size(); ++i) {

    }

    for (std::size_t i = 0; i < this->static_player_texts.size(); ++i) {

    }
}

void game::update()
{
    for (std::size_t i = 0; i < this->players_.size(); ++i) {

        //player update
        this->players_[i].update(this->window_->getSize());

        //bullets update
        for (std::size_t k = 0; k < this->players_[i].get_bullets().size(); ++k) {

            this->players_[i].get_bullets()[k].update();

            if (this->players_[i].get_bullets()[k].get_position().x > this->window_->getSize().x) {
                this->players_[i].get_bullets().erase(this->players_[i].get_bullets().begin() + static_cast<int>(k));
                break;
            }

            //Enemy collision check
        }
    }

    //update UI
    this->UIupdate();
}

void game::draw()
{
    this->window_->clear();

    for (std::size_t i = 0; i < this->players_.size(); ++i) {
        players_[i].draw(*this->window_);
    }

    this->window_->display();
}
