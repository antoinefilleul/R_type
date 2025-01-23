#include <SFML/Graphics.hpp>
#include "IGraphic.hpp"

class Graphic : public IGraphic {
public:
    Graphic();

    ~Graphic();

    void createWindow(int width, int height, const std::string& title) override;

    void clearWindow() override;

    void displayWindow() override;

    bool isWindowOpen() const override;

    void pollEvents() override;

    void draw(const sf::Drawable& drawable) override;

    // New functions for sprites
    bool loadTexture(const std::string& filename, sf::Texture& texture);
    void drawSprite(const sf::Sprite& sprite);
    sf::RenderWindow* getWindow(); // Add this method

private:
    sf::RenderWindow* window;
};