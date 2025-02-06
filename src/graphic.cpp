#include "../include/graphic/graphic.hpp"
#include <SFML/Window/Event.hpp>

Graphic::Graphic() : window(nullptr) {}

Graphic::~Graphic() {
    if (window) {
        delete window;
    }
}

void Graphic::createWindow(int width, int height, const std::string& title) {
    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

void Graphic::clearWindow() {
    if (window) {
        window->clear();
    }
}

void Graphic::displayWindow() {
    if (window) {
        window->display();
    }
}

bool Graphic::isWindowOpen() const {
    return window && window->isOpen();
}

void Graphic::pollEvents() {
    if (window) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                direction = event.key.code;
            }
        }
    }
}

void Graphic::draw(const sf::Drawable& drawable) {
    if (window) {
        window->draw(drawable);
    }
}

sf::Keyboard::Key Graphic::getDirection() const {
    return direction;
}

bool Graphic::loadTexture(const std::string& filename, sf::Texture& texture) {
    return texture.loadFromFile(filename);
}

void Graphic::drawSprite(const sf::Sprite& sprite) {
    if (window) {
        window->draw(sprite);
    }
}

sf::RenderWindow* Graphic::getWindow() {
    return window;
}