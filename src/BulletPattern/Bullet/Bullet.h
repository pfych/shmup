#include "SFML/Graphics/RenderWindow.hpp"
#include "../../Point/Point.h"

class Bullet {
public:
    Bullet(float _speed, int _identifier);

    void update(float deltaTime, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window) const;

private:
    int identifier;
    float distance;
    float speed;
    Coordinate position;

    // For Debug - Visualise the bullets
    bool debug;
    std::vector<Point> points;
    std::vector<Point> middles;
};
