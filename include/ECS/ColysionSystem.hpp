#pragma once
#include "SparseEntityArray.hpp"
class ColysionSystem {
    public:
        ColysionSystem();
        ~ColysionSystem();
        void run(SparseEntityArray entities, sf::Time elapsed);
};