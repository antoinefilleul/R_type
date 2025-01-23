#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "../include/graphic/graphic.hpp" // Include the header file for the Graphic class
#include "ECS/SpeedSystem.hpp" // Include the header file for the SpeedSystem class
#include "ECS/ColysionSystem.hpp" // Include the header file for the ColysionSystem class
class App {
    public:
        App();
        ~App();
        void parse();
        void run();
        SparseEntityArray entities;
    private:
        Graphic graphic;
        ColysionSystem colysionSystem;
        SpeedSystem speedSystem;
        sf::Clock clock; // Add the clock member

};