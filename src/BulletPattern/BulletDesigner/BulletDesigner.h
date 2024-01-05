#include "SFML/Graphics/RenderWindow.hpp"
#include "../../Point/Point.h"

class BulletDesigner {
public:
    BulletDesigner(
            float _speed,
            int _identifier,
            std::string _name,
            const std::vector<Point> &_points,
            bool _isClone,
            int _cloneOf,
            Coordinate _offset,
            float _rotation
    );

    void update(
            float deltaTime,
            sf::Vector2f mousePositionInView,
            const std::vector<BulletDesigner> &existingBullets
    );

    void draw(sf::RenderWindow &window) const;

    std::string name;
    float speed;
    std::vector<Point> points;
    bool isClone;
    int cloneOf;
    Coordinate offset;
    float rotation;
private:
    bool debug;
    int identifier;
    Coordinate position;


};
