#pragma once
#include "ISystems.hpp"

class InputSystem : public ISystem {
    public:
        InputSystem() = default;
        ~InputSystem() = default;
        void run(context& context) override;
};