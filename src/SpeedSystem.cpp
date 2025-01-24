#include "../include/ECS/SpeedSystem.hpp"

void SpeedSystem::run(context& context) {
    float seconds = context.elapsed->asSeconds();
    for (auto& pair : context.entities->getEntities()) {
        pair.second.pos.first += pair.second.speed.first * seconds;
        pair.second.pos.second += pair.second.speed.second * seconds;
    }
}