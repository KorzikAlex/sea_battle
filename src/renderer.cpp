#include "renderer.hpp"

void Renderer::drawGrid(sf::RenderWindow &window, int startX, int startY) {
    for (int i = 0; i <= gridWidth; ++i) {
        // Вертикальные линии
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(startX + i * cellSize, startY)),
            sf::Vertex(sf::Vector2f(startX + i * cellSize, startY + gridHeight * cellSize))
        };
        window.draw(line, 2, sf::Lines);
    }
    for (int i = 0; i <= gridHeight; ++i) {
        // Горизонтальные линии
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(startX, startY + i * cellSize)),
            sf::Vertex(sf::Vector2f(startX + gridWidth * cellSize, startY + i * cellSize))
        };
        window.draw(line, 2, sf::Lines);
    }
};

