#ifndef IGRAPHIC_HPP
#define IGRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <string>

class IGraphic {
public:
    virtual ~IGraphic() = default;

    virtual void createWindow(int width, int height, const std::string& title) = 0;
    virtual void clearWindow() = 0;
    virtual void displayWindow() = 0;
    virtual bool isWindowOpen() const = 0;
    virtual void pollEvents() = 0;
    virtual void draw(const sf::Drawable& drawable) = 0;
};

#endif // IGRAPHIC_HPP