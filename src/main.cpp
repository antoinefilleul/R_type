#include <string> // Include the string library
#include "../include/graphic/graphic.hpp" // Include the header file for the Graphic class

int main() {
    Graphic graphic;
    graphic.createWindow(800, 600, "SFML Window");

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);

    while (graphic.isWindowOpen()) {
        graphic.pollEvents();

        graphic.clearWindow();
        graphic.draw(shape);
        graphic.displayWindow();
    }

    return 0;
}