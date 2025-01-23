#include <SFML/Graphics.hpp>
#include "IGraphic.hpp"

class Graphic : public IGraphic {
public:
    Graphic() : window(nullptr) {}

    ~Graphic() {
        if (window) {
            delete window;
        }
    }

    void createWindow(int width, int height, const std::string& title) override {
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    }

    void clearWindow() override {
        if (window) {
            window->clear();
        }
    }

    void displayWindow() override {
        if (window) {
            window->display();
        }
    }

    bool isWindowOpen() const override {
        return window && window->isOpen();
    }

    void pollEvents() override {
        if (window) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
            }
        }
    }

    void draw(const sf::Drawable& drawable) override {
        if (window) {
            window->draw(drawable);
        }
    }

private:
    sf::RenderWindow* window;
};