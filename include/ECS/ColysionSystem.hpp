#pragma once
#include "ISystems.hpp"

class ColysionSystem : public ISystem{
    public:
        ColysionSystem() = default;
        ~ColysionSystem() = default;
        void run(context& context) override;
};