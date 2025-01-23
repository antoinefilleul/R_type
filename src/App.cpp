#include "../include/App.hpp"

App::App(){
    graphic.createWindow(800, 600, "SFML Window");
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);
    graphic.getWindow()->setFramerateLimit(60);
    parse();
}

App::~App(){

}

using json = nlohmann::json;

void App::parse() {
    std::ifstream file("config.json");
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
            key, // Use the key as the entity name
            value["sprite"],
            std::stoi(value["collision_damage"].get<std::string>()),
            1,
            std::make_pair(std::stoi(value["speedx"].get<std::string>()), std::stoi(value["speedy"].get<std::string>()))
        );
        entities.addEntity(index++, entity);
    }
}

void App::run(){
    while (graphic.isWindowOpen()) {
        graphic.pollEvents();
        sf::Time elapsed = clock.restart();

        graphic.clearWindow();
        colysionSystem.run(entities, elapsed);
        speedSystem.run(entities, elapsed);
        for (const auto& pair : entities.getEntities()) {
            int index = pair.first;
            const Entity& entity = pair.second;
            graphic.draw(entity.drawable);
        }
        graphic.displayWindow();
    }
}