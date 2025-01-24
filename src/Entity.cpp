#include "../include/ECS/Entity.hpp"
#include <iostream>

Entity::Entity() {
}

Entity::Entity(int hp, const std::string& name, const std::string& spriteFile, int collision_damage, int player, std::pair<int, int> pos, std::pair<int, int> speed, int animation, sf::Vector2i frameSize): hp(hp), name(name), collision_damage(collision_damage), player(player), pos(pos), speed(speed), animation(animation), spriteIndex(0), frameSize(frameSize) {
    try {
    texture.loadFromFile(spriteFile);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    } catch (const std::exception& e) {
        std::cerr << "Could not load texture: " << e.what() << std::endl;
    }
}