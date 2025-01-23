#pragma once

#include <unordered_map>
#include "Entity.hpp"

class SparseEntityArray {
public:
    void addEntity(int index, const Entity& entity) {
        entities.emplace(index, entity);
    }

    void removeEntity(int index) {
        entities.erase(index);
    }

    Entity* getEntity(int index) {
        auto it = entities.find(index);
        if (it != entities.end()) {
            return &it->second;
        }
        return nullptr;
    }

    bool hasEntity(int index) const {
        return entities.find(index) != entities.end();
    }
    std::unordered_map<int, Entity>& getEntities() {
        return entities;
    }
private:
    std::unordered_map<int, Entity> entities;
};