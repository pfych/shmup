#include "SFML/Graphics/RenderWindow.hpp"
#include "../../Point/Point.h"

class BulletDesigner {
public:
    BulletDesigner(float _speed, int _identifier);

    void update(
            float deltaTime,
            sf::Vector2f mousePositionInView,
            const std::vector<BulletDesigner> &existingBullets
    );

    void draw(sf::RenderWindow &window) const;

    float speed;
    std::vector<Point> points;
private:
    std::string name;
    bool debug;
    int identifier;
    Coordinate position;

    // For clones
    bool isClone;
    int cloneOf;
    Coordinate offset;
    float rotation;
};
