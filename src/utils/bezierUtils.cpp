#include "../Point/Point.h"
#include "SFML/Graphics.hpp"


template<typename T>
Coordinate lerp(const T &start, const T &end, float distance) {
    // https://www.summbit.com/blog/bezier-curve-guide/
    // We're making a triangle - these variables are the height of each side
    // Multiplying this by distance as range (0->1) scales the triangle.
    float yHeight = (end.y - start.y) * distance;
    float xWidth = (end.x - start.x) * distance;

    // Adding the length of these sides to the start position gets us a position between the points
    return Coordinate{
            .x = start.x + xWidth,
            .y = start.y + yHeight
    };
}

Coordinate BezierPoint(Point &start, Point &control, Point &end, float distance) {
    return lerp(
            lerp(start, control, distance),
            lerp(control, end, distance),
            distance
    );
}

// @TODO This could 100% be more efficient but I wanted to keep this understandable for future me. This might be shit but it's easier to understand at a glance. OPTIMISE LATER!!!
Coordinate BezierPoint(Point &start, Point &control, Point &control2, Point &end, float distance) {
    return lerp(
            BezierPoint(start, control, control2, distance),
            BezierPoint(control, control2, end, distance),
            distance
    );
}

// @TODO Learn why these are pointers, my IDE auto-did this not sure why. Need to learn more!
sf::VertexArray createLine(const Point *start, const Point *end) {
    sf::VertexArray line(sf::LineStrip, 2);
    line[0].position = sf::Vector2f(start->x + 5, start->y + 5);
    line[1].position = sf::Vector2f(end->x + 5, end->y + 5);

    return line;
}