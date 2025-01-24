#include "../include/App.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <fstream>
#include "../include/ECS/SpeedSystem.hpp"
#include "../include/ECS/ColysionSystem.hpp"
#include "../include/ECS/AnimationSystem.hpp"
#include "../include/ECS/InputSystem.hpp"
App::App(){
    graphic.createWindow(800, 600, "SFML Window");
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);
    graphic.getWindow()->setFramerateLimit(60);
    systems.push_back(std::make_unique<ColysionSystem>());
    systems.push_back(std::make_unique<SpeedSystem>());
    systems.push_back(std::make_unique<AnimationSystem>());
    systems.push_back(std::make_unique<InputSystem>());
    parse();
}

App::~App(){

}

using json = nlohmann::json;

void App::parse() {
    std::ifstream file("../config.json");
    if (!file.is_open()) {
        std::cerr << "Could not open config.json" << std::endl;
        return;
    }

    json config;
    file >> config;

    int index = 0;
    for (const auto& [key, value] : config.items()) {
        Entity entity(
            value["hp"],
            key,
            value["sprite"],
            std::stoi(value["collision_damage"].get<std::string>()),
            key == "player" ? 1 : 0,
            std::make_pair(std::stoi(value["x"].get<std::string>()), std::stoi(value["y"].get<std::string>())),
            std::make_pair(std::stoi(value["speedx"].get<std::string>()), std::stoi(value["speedy"].get<std::string>())),
            std::stoi(value["animation"].get<std::string>()),
            sf::Vector2i(std::stoi(value["spritesize"].get<std::string>()), std::stoi(value["spritesize"].get<std::string>()))
        );
        entities.addEntity(index++, entity);
    }
}

void App::run(){
    while (graphic.isWindowOpen()) {
        graphic.pollEvents();
        sf::Time elapsed = clock.restart();

        graphic.clearWindow();
        for (auto& system : systems) {
            context ctx{&entities, &elapsed, graphic.getWindow()};
            system->run(ctx);
        }
        for (const auto& pair : entities.getEntities()) {
            int index = pair.first;
            const Entity& entity = pair.second;
            graphic.draw(entity.sprite);
        }
        graphic.displayWindow();
    }
}