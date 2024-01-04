#include "../../Point/Point.h"

class Bullet {
public:
    Bullet(float _speed, std::vector<Point> _points);

    void update(float deltaTime);

    void draw(sf::RenderWindow &window) const;

    bool isOffScreen(sf::RenderWindow &window) const;

private:
    float distance;
    float speed;
    Coordinate position{};
    std::vector<Point> points;
};
