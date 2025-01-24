#include "../include/ECS/ColysionSystem.hpp"

void ColysionSystem::run(context& context) {
    std::vector<int> entitiesToRemove;

    for (auto& pair : context.entities->getEntities()) {
        for (auto& pairother : context.entities->getEntities()) {
            if (&pair.second != &pairother.second) {
                if (pair.second.lastHitClock.getElapsedTime().asSeconds() >= 1.0f) {
                        pair.second.hp -= pairother.second.collision_damage;
                        pair.second.lastHitClock.restart();
                    }
                    if (pairother.second.lastHitClock.getElapsedTime().asSeconds() >= 1.0f) {
                        pairother.second.hp -= pair.second.collision_damage;
                        pairother.second.lastHitClock.restart();
                    }
            }
        }
    }

    for (auto& pair : context.entities->getEntities()) {
        if (pair.second.hp <= 0) {
            entitiesToRemove.push_back(pair.first);
        }
    }

    for (int index : entitiesToRemove) {
        context.entities->removeEntity(index);
    }
}