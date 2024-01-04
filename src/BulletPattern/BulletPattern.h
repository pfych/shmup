#include "SFML/Graphics/RenderWindow.hpp"
#include "Bullet/BulletDesigner.h"

class BulletPattern {
public:
    BulletPattern();

    void update(float deltaTime, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

private:
    std::string patternName;
    std::vector<BulletDesigner> bulletDesignerBullets;
};