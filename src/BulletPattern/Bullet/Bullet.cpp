#include "Bullet.h"
#include "../../utils/bezierUtils.h"
#include <utility>

Bullet::Bullet(float _speed, std::vector<Point> _points) :
        speed(_speed),
        points(std::move(_points)) {
    distance = 0;
}

void Bullet::update(float deltaTime) {
    float distanceAsRange = distance / 100;

    distance += speed * deltaTime;

    if (points.size() == 2) {
        position = lerp(points[0], points[1], distanceAsRange);
    } else if (points.size() == 3) {
        position = BezierPoint(points[0], points[1], points[2], distanceAsRange);
    } else if (points.size() == 4) {
        position = BezierPoint(points[0], points[1], points[2], points[3], distanceAsRange);
    }
}

void Bullet::draw(sf::RenderWindow &window) const {
    sf::CircleShape bulletShape(5.f);
    bulletShape.setFillColor(sf::Color(0, 0, 255));
    bulletShape.setPosition(position.x, position.y);
    window.draw(bulletShape);
}

bool Bullet::isOffScreen(sf::RenderWindow &window) const {
    return position.y > window.getSize().y || position.y < 0 || position.x > window.getSize().x || position.x < 0;
}