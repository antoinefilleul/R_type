#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>

class Entity {
    public:
        Entity();
        Entity(int hp, const std::string& name, const std::string& spriteFile, int collision_damage, int player, std::pair<int, int> pos, std::pair<int, int> speed, int animation, sf::Vector2i frameSize);
        ~Entity() = default;
        std::string name;
        int hp;
        int collision_damage;
        int player;
        std::pair<int, int> pos;
        std::pair<int, int> speed;

        int animation;
        int spriteIndex;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Clock lastHitClock;
        sf::Vector2i frameSize;
        void updateSprite() {
            int left = spriteIndex * frameSize.x;
            sprite.setTextureRect(sf::IntRect(left, 0, frameSize.x, frameSize.y));
        }
};