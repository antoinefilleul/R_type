#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>
#include "ECS/ISystems.hpp"
#include "../include/graphic/graphic.hpp"
#include "ECS/SparseEntityArray.hpp"

class App {
    public:
        App();
        ~App();
        void parse();
        void run();
        SparseEntityArray entities;
    private:
        Graphic graphic;
        std::vector<std::unique_ptr<ISystem>> systems;
        sf::Clock clock;

};