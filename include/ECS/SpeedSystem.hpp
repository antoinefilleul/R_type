#pragma once
#include "ISystems.hpp"
class SpeedSystem : public ISystem{
    public:
        SpeedSystem() = default;
        ~SpeedSystem() = default;
        void run(context& context) override;
};