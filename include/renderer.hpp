#ifndef SEABATTLE_INCLUDE_RENDERER_HPP
#define SEABATTLE_INCLUDE_RENDERER_HPP

#include <SFML/Graphics.hpp>

class Renderer {
public:
    Renderer();
    void drawGrid(sf::RenderWindow &window, int startX, int startY);
    ~Renderer();

private:
    sf::RenderWindow window;
};

#endif // SEABATTLE_INCLUDE_RENDERER_HPP
