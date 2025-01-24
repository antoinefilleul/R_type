#include "../include/ECS/InputSystem.hpp"

void InputSystem::run(context& context) {
    sf::Event event;
    while (context.window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            context.window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            for (auto& pair : context.entities->getEntities()) {
                Entity& entity = pair.second;
                if (entity.name == "Player") {
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                            entity.speed.second = -100; // Move up
                            break;
                        case sf::Keyboard::S:
                            entity.speed.second = 100; // Move down
                            break;
                        case sf::Keyboard::A:
                            entity.speed.first = -100; // Move left
                            break;
                        case sf::Keyboard::D:
                            entity.speed.first = 100; // Move right
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            for (auto& pair : context.entities->getEntities()) {
                Entity& entity = pair.second;
                if (entity.name == "Player") {
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                        case sf::Keyboard::S:
                            entity.speed.second = 0; // Stop vertical movement
                            break;
                        case sf::Keyboard::A:
                        case sf::Keyboard::D:
                            entity.speed.first = 0; // Stop horizontal movement
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}