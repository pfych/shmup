#include "SFML/Graphics/RenderWindow.hpp"
#include "../../Point/Point.h"

class BulletDesigner {
public:
    BulletDesigner(float _speed, int _identifier);

    void update(float deltaTime, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window) const;

    float speed;
    std::vector<Point> points;
private:
    bool debug;
    int identifier;
    Coordinate position;
    std::vector<Point> middles;
};
