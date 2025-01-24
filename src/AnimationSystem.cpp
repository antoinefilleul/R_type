#include "../include/ECS/AnimationSystem.hpp"

void AnimationSystem::run(context& context) {
    for (auto& pair : context.entities->getEntities()) {
        pair.second.spriteIndex++;
        if (pair.second.spriteIndex >= pair.second.animation) {
            pair.second.spriteIndex = 0;
        }
        pair.second.updateSprite();
    }
}