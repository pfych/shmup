#include "Point.h"

Point::Point(float _x, float _y, bool _dragable) {
    x = _x;
    y = _y;
    isDragging = false;
    dragable = _dragable;
    shape = sf::CircleShape(5.f);
    color = sf::Color(255, 0, 0);
}

void Point::update(float deltaTime, sf::Vector2f mousePositionInView) {
    shape.setPosition(x, y);

    if (dragable) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


            if (shape.getGlobalBounds().contains(mousePositionInView)) {
                isDragging = true;
            }

            if (isDragging) {

                x = mousePositionInView.x - 5;
                y = mousePositionInView.y - 5;
            }
        } else {
            isDragging = false;
        }
    }
}

void Point::draw(sf::RenderWindow &window) {
    shape.setPosition(x, y);
    shape.setFillColor(color);
    window.draw(shape);
}