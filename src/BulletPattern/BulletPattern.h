#include "SFML/Graphics/RenderWindow.hpp"
#include "BulletDesigner/BulletDesigner.h"
#include "Bullet/Bullet.h"

class BulletPattern {
public:
    BulletPattern();

    void update(float deltaTime, sf::RenderWindow &window, sf::Clock clock);

    void draw(sf::RenderWindow &window);

private:
    std::string patternName;
    bool isFiring;
    int shots;
    int betweenDelayMs;
    int shotsLeft;
    int lastShootTimeMs;
    std::vector<BulletDesigner> bulletDesignerBullets;
    std::vector<Bullet> bullets;
};