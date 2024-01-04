#include "SFML/Graphics/RenderWindow.hpp"
#include "BulletDesigner/BulletDesigner.h"
#include "Bullet/Bullet.h"

class BulletPattern {
public:
    BulletPattern();

    void update(float deltaTime, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

private:
    std::string patternName;
    std::vector<BulletDesigner> bulletDesignerBullets;
    std::vector<Bullet> bullets;
};