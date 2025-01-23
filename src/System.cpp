#include "../include/ECS/ColysionSystem.hpp"

ColysionSystem::ColysionSystem() {
}

ColysionSystem::~ColysionSystem() {
}

void ColysionSystem::run(SparseEntityArray entities, sf::Time elapsed) {
    std::vector<int> entitiesToRemove;

    for (auto& pair : entities.getEntities()) {
        for (auto& pairother : entities.getEntities()) {
            if (&pair.second != &pairother.second) {
                if (pair.second.pos.first == pairother.second.pos.first && pair.second.pos.second == pairother.second.pos.second) {
                    pair.second.hp -= pairother.second.collision_damage;
                    pairother.second.hp -= pair.second.collision_damage;
                }
            }
        }
    }

    for (auto& pair : entities.getEntities()) {
        if (pair.second.hp <= 0) {
            entitiesToRemove.push_back(pair.first);
        }
    }

    for (int index : entitiesToRemove) {
        entities.removeEntity(index);
    }
}