#pragma once

#include "SFML/Graphics.hpp"

struct Coordinate {
    float x;
    float y;
};

class Point {
public:
    float x;
    float y;

    Point(float _x, float _y, bool _dragable, sf::Color color);

    void update(float deltaTime, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

private:
    bool isDragging;
    bool dragable;
    sf::CircleShape shape;
};