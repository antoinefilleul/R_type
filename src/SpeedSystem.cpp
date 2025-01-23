#include "../include/ECS/SpeedSystem.hpp"

SpeedSystem::SpeedSystem() {
}

SpeedSystem::~SpeedSystem() {
}

void SpeedSystem::run(SparseEntityArray entities, sf::Time elapsed) {
    float seconds = elapsed.asSeconds();
    for (auto& pair : entities.getEntities()) {
        pair.second.pos.first += pair.second.speed.first * seconds;
        pair.second.pos.second += pair.second.speed.second * seconds;
    }
}