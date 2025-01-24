#pragma once
#include "SparseEntityArray.hpp"
#include <SFML/System/Time.hpp>
struct context {
    SparseEntityArray* entities;
    sf::Time *elapsed;
    sf::RenderWindow* window;
};

class ISystem {
    public:
        virtual void run(context& context) = 0;
};