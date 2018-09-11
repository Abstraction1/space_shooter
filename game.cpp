#include "game.h"

game::game(sf::RenderWindow *window)
{
    this->window_ = window;
    this->window_->setFramerateLimit(60);

    //init fonts
    this->font_.loadFromFile("./Fonts/Dosis-Light.ttf");

    //init texture
    this->player_texture_.loadFromFile("./Textures/Ship/ship.png");
    this->bullet_texture_.loadFromFile("./Textures/Guns/missileTex01.png");
    this->gun_texture_01_.loadFromFile("./Textures/Guns/gun01.png");

    //init player
    this->players_.push_back(player(&player_texture_, &bullet_texture_, &gun_texture_01_));

    //this->players_.push_back(player(&player_texture_, &bullet_texture_
                                    //, sf::Keyboard::I, sf::Keyboard::K
                                    //, sf::Keyboard::L, sf::Keyboard::RShift));

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
    sf::Text temp_text;

    for (std::size_t i = 0; i < this->players_.size(); ++i) {
        
        //follow text init
        temp_text.setFont(font_);
        temp_text.setCharacterSize(14);
        temp_text.setFillColor(sf::Color::White);
        temp_text.setString(std::to_string(i));

        this->follow_player_texts.push_back(sf::Text(temp_text));
        
        //static text inits
        temp_text.setFont(font_);
        temp_text.setCharacterSize(14);
        temp_text.setFillColor(sf::Color::White);
        temp_text.setString("");

        this->static_player_texts.push_back(sf::Text(temp_text));        
    }
}

void game::UIupdate()
{
    for (std::size_t i = 0; i < this->follow_player_texts.size(); ++i) {
        this->follow_player_texts[i].setPosition(this->players_[i].get_position().x, this->players_[i].get_position().y - 20.f);
        this->follow_player_texts[i].setString(std::to_string(i) + "        -        " + this->players_[i].get_hp_as_string());
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

void game::drawUI() {
    for(std::size_t i = 0; i < this->follow_player_texts.size(); ++i) {
        this->window_->draw(this->follow_player_texts[i]);
    }

    for(std::size_t i = 0; i < this->static_player_texts.size(); ++i) {
        this->window_->draw(this->static_player_texts[i]);        
    }
}

void game::draw()
{
    this->window_->clear();

    for (std::size_t i = 0; i < this->players_.size(); ++i) {
        players_[i].draw(*this->window_);
    }

    this->drawUI();
    this->window_->display();
}
