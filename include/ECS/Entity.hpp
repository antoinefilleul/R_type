#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>

class Entity {
    public:
        Entity();
        Entity(int hp, std::string name, std::string sprite, int player, int collision_damage, std::pair<int, int> speed);
        int hp;
        std::pair<int, int> pos;
        std::string name;
        std::string sprite;
        int player;
        int collision_damage;
        std::pair<int, int> speed;
        sf::Drawable &drawable;
        
};