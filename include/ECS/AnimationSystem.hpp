#pragma once
#include "ISystems.hpp"

class AnimationSystem : public ISystem {
public:
    AnimationSystem() = default;
    ~AnimationSystem() = default;
    void run(context& context) override;
};