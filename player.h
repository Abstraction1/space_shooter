#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"

class player
{
public:
    player(sf::Texture *t, sf::Texture *bullet_t, sf::Texture *main_gun_texture, int UP = 22, int DOWN = 18, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
    virtual ~player();

    //accessors
    inline std::vector<bullet>& get_bullets()       { return this->bullets_; }
    inline const sf::Vector2f& get_position() const { return this->sprite_.getPosition(); }
    inline const sf::String get_hp_as_string()      { return std::to_string(this->hp_) + "/" + std::to_string(this->hp_next_); }

    //setters

    //functions
    void update_accessories();
    void combat();
    void movement();
    void update(sf::Vector2u window_bounds);
    void draw(sf::RenderTarget &target);

    //statics
    static unsigned players;
private:
    int level_;
    int exp_;
    int exp_next_;
    int hp_;
    int hp_next_;
    int damage_;
    int damage_max_;
    int score_;

    int shooter_timer_;
    int shooter_timer_max_;
    int damage_timer_;
    int damage_timer_max_;
    
    int controls[5];
    
    sf::Vector2f current_velocity_;
    float max_velocity_;
    float acceleration_;
    sf::Vector2f direction_;
    float stabilizer_force_;

    sf::Texture *bullet_texture_;
    std::vector <bullet> bullets_;
    
    unsigned player_number;
    sf::Texture *texture_;
    sf::Texture gun_texture_01_;
   
    sf::Sprite sprite_;
    sf::RectangleShape hit_box_;
    sf::Vector2f player_center_;

    sf::Sprite main_gun_sprite_;
    sf::Texture *main_gun_texture_;
};

#endif // PLAYER_H
