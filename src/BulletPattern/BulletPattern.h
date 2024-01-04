#include "SFML/Graphics/RenderWindow.hpp"
#include "BulletDesigner/BulletDesigner.h"
#include "Bullet/Bullet.h"

class BulletPattern {
public:
    BulletPattern(int _identifier);

    void update(float deltaTime, sf::RenderWindow &window, sf::View &view, sf::Clock clock);

    void draw(sf::RenderWindow &window);

private:
    std::string patternName;
    int identifier;
    bool isFiring;
    int shots;
    int betweenDelayMs;
    int shotsLeft;
    int lastShootTimeMs;
    std::vector<BulletDesigner> bulletDesignerBullets;
    std::vector<Bullet> bullets;
};