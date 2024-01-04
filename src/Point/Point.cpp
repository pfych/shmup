#include "Point.h"

Point::Point(float _x, float _y, bool _dragable, sf::Color color) {
    x = _x;
    y = _y;
    isDragging = false;
    dragable = _dragable;
    shape = sf::CircleShape(5.f);
    shape.setFillColor(color);
}

void Point::update(float deltaTime, sf::RenderWindow &window) {
    shape.setPosition(x, y);
    
    if (dragable) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2 mousePosition = sf::Mouse::getPosition(window);

            if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isDragging = true;
            }

            if (isDragging) {
                x = mousePosition.x - 5;
                y = mousePosition.y - 5;
            }
        } else {
            isDragging = false;
        }
    }
}

void Point::draw(sf::RenderWindow &window) {
    shape.setPosition(x, y);
    window.draw(shape);
}