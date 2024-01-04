#include "../../Point/Point.h"

class Bullet {
public:
    Bullet(float _speed, std::vector<Point> _points);

    void update(float deltaTime, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);


private:
    float distance;
    float speed;
    Coordinate position;
    std::vector<Point> points;
};
