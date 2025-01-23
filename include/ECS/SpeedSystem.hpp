#pragma once
#include "SparseEntityArray.hpp"

class SpeedSystem {
    public:
        SpeedSystem();
        ~SpeedSystem();
        void run(SparseEntityArray entities, sf::Time elapsed);
};